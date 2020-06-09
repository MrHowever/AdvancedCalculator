//
// Created by mrhowever on 14.10.19.
//

#include "BigInteger.hh"
#include "BigIntegerComparisons.tcc"
#include "BigIntegerArithmeticOperations.tcc"
#include "BigInteger.tcc"
#include "../Transforms/NumberTheoreticTransform.hh"
#include "ModularOperations/ModularOperations.hh"
#include <cmath>

BigInteger BigInteger::operator+(const BigInteger& integer) const
{
    //Make general function and use this?
    if(*this > 0 && integer < 0)
        return *this - abs(integer);
    else if(*this < 0 && integer > 0)
        return integer - abs(*this);
    else if(*this < 0 && integer < 0)
        return -(abs(*this) + abs(integer));


    BigInteger result;
    int biggerSize = std::max(_digits.size(),integer._digits.size());
    uint overflow = 0;

    for(int i = 0; i < biggerSize; i++) {
        if(result._digits.size() == i)
            result._digits.push_back(0);

        result._digits[i] += i < integer._digits.size() ? integer._digits[i] : 0; //+ overflow;
        result._digits[i] += i < _digits.size() ? _digits[i] : 0;
        result._digits[i] += overflow;

        if(DIGIT_MAX - integer._digits[i] - overflow >= _digits[i]) {
            overflow = 0;
        }
        else {
            overflow = 1;
        }
    }

    if(overflow)
        result._digits.push_back(1);

    std::string t = toString();
    std::string i = integer.toString();
    std::string r = result.toString();


    return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& integer)
{
    *this = *this + integer;
    return *this;
}

//TODO should this operator do this?
BigInteger BigInteger::operator+() const
{
    BigInteger integer = *this;
    integer._negative = false;
    return integer;
}

BigInteger BigInteger::operator-(const BigInteger& integer) const
{
    if(*this > 0 && integer < 0)
        return *this + abs(integer);
    else if(*this < 0 && integer > 0)
        return -(abs(*this) + abs(integer));
    else if(*this < 0 && integer < 0)
        return -(abs(integer) - abs(*this));
    else if(*this < integer)
        return -(integer - *this);

    BigInteger result(*this);

    for(int i = 0; i < integer._digits.size(); i++) {
        if(result._digits[i] < integer._digits[i]) {
            result._digits[i + 1]--;
            uint64_t temp = result._digits[i];
            result._digits[i] = DIGIT_MAX - integer._digits[i];
            result._digits[i] +=  temp + 1;
        }
        else
            result._digits[i] -= integer._digits[i];
    }

    std::string t = toString();
    std::string i = integer.toString();
    std::string r = result.toString();

    return result;
}

BigInteger& BigInteger::operator-=(const BigInteger& integer)
{
    *this = *this - integer;
    return *this;
}

BigInteger BigInteger::operator-() const
{
    BigInteger result = *this;
    result._negative = !result._negative;
    return result;
}

BigInteger BigInteger::operator*(const BigInteger& integer) const
{
    
    return schoolbookMultiplication(integer);
}

BigInteger& BigInteger::operator*=(const BigInteger& integer)
{
    *this = *this * integer;
    return *this;
}


BigInteger BigInteger::schoolbookMultiplication(const BigInteger& integer) const
{
    BigInteger result;

    for(int i = 0; i < integer._digits.size(); i++) {
        for(int j = 0; j < _digits.size(); j++) {
            if(result._digits.size() == (i+j)) {
                result._digits.push_back(0);
            }

            uint64_t previousValue = result._digits[i+j];

            result._digits[i+j] += integer._digits[i] * _digits[j];

            __uint128_t overflow = (((__uint128_t) integer._digits[i]) * ((__uint128_t) _digits[j]) + previousValue) / (((__uint128_t) DIGIT_MAX) + 1);

            //TODO base = maxvalue + 1, add?
            if(_digits[j] != 0) {
                if (DIGIT_MAX / _digits[j] < integer._digits[i]) {
                    if (result._digits.size() <= (i + j + 1)) {
                        result._digits.push_back(overflow);
                    } else {
                        result._digits[i + j + 1] += overflow;
                    }
                }
            }
        }
    }

    result._negative = _negative != integer._negative;
    return result;
}

BigInteger BigInteger::karatsubaMultiplication(const BigInteger& integer)
{
    if(*this < DIGIT_MAX || integer < DIGIT_MAX)
        return schoolbookMultiplication(integer);

    uint64_t halfSize = (uint64_t) std::floor(std::min(_digits.size(),integer._digits.size()) / 2);
    
    BigInteger x1(std::vector<uint64_t>(_digits.begin() + halfSize, _digits.end()));
    BigInteger x2(std::vector<uint64_t>(_digits.begin(), _digits.begin() + halfSize));
    BigInteger y1(std::vector<uint64_t>(integer._digits.begin() + halfSize, integer._digits.end()));
    BigInteger y2(std::vector<uint64_t>(integer._digits.begin(), integer._digits.begin() + halfSize));

    BigInteger F(x1.karatsubaMultiplication(y1));
    BigInteger G(x2.karatsubaMultiplication(y2));
    BigInteger H((x1 + x2).karatsubaMultiplication(y1 + y2));
    BigInteger K(H - F - G);

    return G + K*pow(BASE,halfSize) + F*pow(BASE,2*halfSize);
}

BigInteger BigInteger::toomCookMultiplication(const BigInteger& integer) {

    //TODO experiment with best values to switch to schoolbook
    if(_digits.size() < 3|| integer._digits.size() < 3)
        return schoolbookMultiplication(integer);

    uint64_t basePower =
            std::max(std::ceil(std::ceil(std::log(_digits.size()) / std::log(18446744073709551616.0l)) / 3.0),
                     std::ceil(std::ceil(std::log(integer._digits.size()) / std::log(18446744073709551616.0l)) / 3.0)) +
            1;

    uint64_t biggerSize = std::max(_digits.size(), integer._digits.size());
    uint64_t partSize = biggerSize % 3 == 0 ? biggerSize / 3 : biggerSize / 3 + 1;

    std::vector<BigInteger> newBaseFirst = splitIntoParts(partSize);
    std::vector<BigInteger> newBaseSecond = integer.splitIntoParts(partSize);

    for(int i = 1; i < 3; i++) {
        if(newBaseFirst.size() == i)
            newBaseFirst.emplace_back(0);
        if(newBaseSecond.size() == i)
            newBaseSecond.emplace_back(0);
    }

    BigInteger p0 = newBaseFirst[0] + newBaseFirst[2];
    BigInteger p_0 = newBaseFirst[0];
    BigInteger p_1 = p0 + newBaseFirst[1];
    BigInteger p_minus1(p0 - newBaseFirst[1]);
    BigInteger p_minus2 = (p_minus1 + newBaseFirst[2]) * 2 - newBaseFirst[0];
    BigInteger p_inf = newBaseFirst[2];

    BigInteger q0 = newBaseSecond[0] + newBaseSecond[2];
    BigInteger q_0 = newBaseSecond[0];
    BigInteger q_1 = q0 + newBaseSecond[1];
    BigInteger q_minus1 = q0 - newBaseSecond[1];
    BigInteger q_minus2 = (q_minus1 + newBaseSecond[2]) * 2 - newBaseSecond[0];
    BigInteger q_inf = newBaseSecond[2];

    BigInteger r_0 = p_0.toomCookMultiplication(q_0);
    BigInteger r_1 = p_1.toomCookMultiplication(q_1);
    BigInteger r_minus1 = p_minus1.toomCookMultiplication(q_minus1);
    BigInteger r_minus2 = p_minus2.toomCookMultiplication(q_minus2);
    BigInteger r_inf = p_inf.toomCookMultiplication(q_inf);

    BigInteger r0 = r_0;
    BigInteger r4 = r_inf;
    BigInteger r3 = (r_minus2 - r_1)/3;
    BigInteger r1 = (r_1 - r_minus1)/2;
    BigInteger r2 = r_minus1 - r_0;
    r3 = (r2 - r3)/2 + r_inf * 2;
    r2 += r1 - r4;
    r1 -= r3;

    BigInteger result = r0;
    result += r1.shiftLeft(BITS_PER_DIGIT * basePower);
    result += r2.shiftLeft(BITS_PER_DIGIT * basePower*2);
    result += r3.shiftLeft(BITS_PER_DIGIT * basePower*3);
    result += r4.shiftLeft(BITS_PER_DIGIT * basePower*4);

    return result;
}

std::vector<BigInteger> BigInteger::splitIntoParts(uint64_t partSize) const
{
    uint64_t i = 0;
    std::vector<BigInteger> result;

    do {
        auto first = _digits.begin() + i;
        auto last = _digits.begin() + i + partSize > _digits.end() ? _digits.end() : _digits.begin() + i + partSize;

        if (first >= _digits.end())
            break;

        result.emplace_back(std::vector<uint64_t>(first, last));
        i += partSize;
    } while (i < _digits.size());

    return result;
}

//TODO optimize
template<typename T>
BigInteger pow(const BigInteger& integer, const T power)
{
    if constexpr(std::is_arithmetic_v<T>) {
        BigInteger result(integer);

        for (int i = 1; i < power; i++) {
            result = result.schoolbookMultiplication(integer);
        }

        return result;
    }
}

BigInteger BigInteger::fftMultiplication(const BigInteger& integer)
{
    uint64_t partCount = std::max(_digits.size(),integer._digits.size()) - 1;
    uint64_t modulus = MC::AF::pow((uint64_t) 2,3*partCount) + 1;
    // partCount +1 to force transformLength to be 8 when supplied size is 4
    uint64_t omega = findNthPrimitiveRoot(modulus,std::round(std::pow(2,std::ceil(std::log2(partCount+1)))));

    MC::MT::NTT<uint64_t> transformer(_digits,omega,modulus);

    auto firstTransform = transformer.transform(_digits);
    auto secondTransform = transformer.transform(integer._digits);

    BigInteger result;

    //TODO change this to generic
    result._digits = std::vector<uint64_t>(firstTransform.size());
    for(int i = 0; i < result._digits.size(); i++) {
        result._digits[i] = MC::MO::modularMult(firstTransform[i],secondTransform[i],modulus);
    }

    result._digits = transformer.inverseTransform(result._digits);

    return result;
}

BigInteger BigInteger::operator/(const BigInteger& integer) const
{
    BigInteger result = *this;

    for(int i = 0; i < integer._digits.size(); i++) {
        for(int j = 0; j < _digits.size(); j++) {
            if(result._digits.size() == (i+j)) {
                result._digits.push_back(0);
            }

            int value = integer._digits[i] * _digits[j];
            result._digits[i+j] += value % 100;

            if(value > 100) {
                if(result._digits.size() < (i+j+1)) {
                    result._digits.push_back(value / 100);
                }
                else {
                    result._digits[i+j+1] += value / 100;
                }
            }
        }
    }

    return result;
}

BigInteger& BigInteger::operator/=(const BigInteger& integer)
{
    *this = *this / integer;
    return *this;
}

BigInteger BigInteger::newtonRaphsonDiv(const BigInteger& integer)
{

}

BigInteger& BigInteger::operator++()
{
    *this += 1;
    return *this;
}

const BigInteger BigInteger::operator++(int)
{
    BigInteger copy(*this);
    ++(*this);
    return copy;
}

BigInteger& BigInteger::operator--()
{
    *this -= 1;
    return *this;
}

const BigInteger BigInteger::operator--(int)
{
    BigInteger copy(*this);
    --(*this);
    return copy;
}

BigInteger BigInteger::operator%(const BigInteger& integer) const
{
    return *this - (integer * (*this / integer));
}

BigInteger& BigInteger::operator%=(const BigInteger& integer)
{
    *this -= integer * (*this / integer);
    return *this;
}