//
// Created by mrhowever on 16.10.19.
//

#ifndef BIGINTEGER_BIGINTEGERARITHMETICOPERATIONS_TCC
#define BIGINTEGER_BIGINTEGERARITHMETICOPERATIONS_TCC

#include <algorithm>
#include "BigInteger.hh"
#include "BigInteger.tcc"
#include "BasicOperations/BasicOperations.hh"

template<typename T> BigInteger BigInteger::operator+(T integer) const
{
    if constexpr(std::is_integral_v<T>) {
        if(integer < 0 && *this > 0)
            return *this - MC::BO::abs(integer);
        else if(*this < 0 && integer > 0)
            return -(abs(*this) - integer);
        else if(*this < 0 && integer < 0)
            return -(abs(*this) + MC::BO::abs(integer));

        BigInteger result(*this);

        if (DIGIT_MAX - integer < *this) {
            if (_digits.size() < 2)
                result._digits.push_back(1);
            else
                result._digits[1]++;
        }
        // Overflow gives the correct value
        result._digits[0] += integer;

        return result;
    }
    else {
        BigInteger value(integer);
        return *this + value;
    }
}

template<typename T> BigInteger& BigInteger::operator+=(T integer)
{
    if constexpr(std::is_integral_v<T>) {
        if(integer < 0 && *this > 0)
            return *this -= MC::BO::abs(integer);
        else if(*this < 0 && integer > 0)
            return *this = -(abs(*this) - integer);
        else if(*this < 0 && integer < 0)
            return *this = -(abs(*this) + MC::BO::abs(integer));

        if (DIGIT_MAX - integer < *this) {
            if (_digits.size() < 2)
                _digits.push_back(1);
            else
                _digits[1]++;
        }
        // Overflow gives the correct value
        _digits[0] += integer;

        return *this;
    }
    else {
        BigInteger value(integer);
        return *this += value;
    }
}

template<typename T> BigInteger BigInteger::operator-(T integer) const
{
    if constexpr(std::is_integral_v<T>) {
        if(*this > 0 && integer < 0)
            return *this + MC::BO::abs(integer);
        else if(*this < 0 && integer > 0)
            return -(abs(*this) + integer);
        else if(*this < 0 && integer < 0)
            return -(abs(*this) - MC::BO::abs(integer));

        BigInteger result(*this);

        if (integer > *this) {
            if (result._digits.size() > 2) {
                int i = 1;

                // Propagate the subtraction to following digits
                while (i < result._digits.size()) {
                    if (result._digits[i] == 1) {
                        if (i == result._digits.size() - 1) {
                            result._digits.pop_back();
                            break;
                        } else {
                            result._digits[i] = 0;
                        }
                    } else if (result._digits[i] == 0) {
                        result._digits[i] = DIGIT_MAX - 1;
                    } else {
                        result._digits[i]--;
                        break;
                    }

                    i++;
                }

                result._digits[0] = DIGIT_MAX - (integer - result._digits[0]);
            } else {
                result._digits[0] = integer - result._digits[0];
                result._negative = true;
            }
        } else {
            result._digits[0] -= integer;
        }

        return result;
    }
    else {
        BigInteger value(integer);
        return *this - value;
    }
}

template<typename T> BigInteger& BigInteger::operator-=(T integer)
{
    if constexpr(std::is_integral_v<T>) {
        if(*this > 0 && integer < 0)
            return *this += MC::BO::abs(integer);
        else if(*this < 0 && integer > 0)
            return *this = -(abs(*this) + integer);
        else if(*this < 0 && integer < 0)
            return *this = -(abs(*this) - MC::BO::abs(integer));

        if (integer > *this) {
            if (_digits.size() > 2) {
                int i = 1;

                // Propagate the subtraction to following digits
                while (i < _digits.size()) {
                    if (_digits[i] == 1) {
                        if (i == _digits.size() - 1) {
                            _digits.pop_back();
                            break;
                        } else {
                            _digits[i] = 0;
                        }
                    } else if (_digits[i] == 0) {
                        _digits[i] = DIGIT_MAX - 1;
                    } else {
                        _digits[i]--;
                        break;
                    }

                    i++;
                }

                _digits[0] = DIGIT_MAX - (integer - _digits[0]);
            } else {
                _digits[0] = integer - _digits[0];
                _negative = true;
            }
        } else {
            _digits[0] -= integer;
        }

        return *this;
    }
    else {
        BigInteger value(integer);
        return *this -= value;
    }
}

template<typename T> BigInteger BigInteger::operator%(T integer) const
{
    BigInteger result = _digits[0] % integer;
    return result;
}

template<typename T> BigInteger& BigInteger::operator%=(T integer)
{
    *this = _digits[0] % integer;
    return *this;
}

template<typename T> BigInteger BigInteger::operator*(T integer) const
{
    BigInteger intgr(integer);
    BigInteger result(*this * intgr);
    return result;
}

template<typename T> BigInteger BigInteger::operator*=(T integer)
{
    BigInteger intgr(integer);
    *this *= intgr;
    return *this;
}

template<typename T> BigInteger BigInteger::operator/(T integer) const
{
    BigInteger result;
    result._digits[0] = _digits[_digits.size() - 1] / integer;

    uint64_t upperIndex = 0;
    for(int i = _digits.size() - 2; i >= 0; i--) {
        uint64_t firstDigit = _digits[i+1] - (result._digits[upperIndex++] * integer);
        uint64_t secondDigit(_digits[i]);

        uint64_t baseDiv = DIGIT_MAX / integer;
        BigInteger tempResult(baseDiv);
        tempResult *= firstDigit;

        uint64_t maximumFit = baseDiv * integer;
        uint64_t complement = -maximumFit;
        double maxFitToComplementRatio = integer / (double) complement;

        uint64_t B = std::floor(firstDigit / maxFitToComplementRatio);
        tempResult += B;

        tempResult += secondDigit / integer;

        BigInteger wholeComplement(complement);
        wholeComplement *= firstDigit;
        BigInteger complementFit(B);
        complementFit *= integer;

        //TODO exception thrown with (uint64_t) cast
        uint64_t baseRemainder = (wholeComplement - complementFit)._digits[0];
        uint64_t secondDigitDivRemainder = (secondDigit % integer);

        //TODO maxvalue + 1, separate function check addition overflow?
        //Overflow occurs
        if(DIGIT_MAX - secondDigitDivRemainder < baseRemainder) {
            tempResult += baseDiv;
            tempResult += (baseRemainder + secondDigitDivRemainder + complement) / integer;
        }   //No overflow occured
        else {
            tempResult += (baseRemainder + secondDigitDivRemainder) / integer;
        }

        result._digits.push_back(tempResult._digits[0]);
    }

    std::reverse(result._digits.begin(), result._digits.end());

    while(result._digits.back() == 0)
        result._digits.pop_back();

    return result;
}

template<typename T> BigInteger BigInteger::operator/=(T integer)
{
    *this = *this / integer;
    return *this;
}
#endif //BIGINTEGER_BIGINTEGERARITHMETICOPERATIONS_TCC
