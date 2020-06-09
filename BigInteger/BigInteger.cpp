#include "BigInteger.hh"
#include "BigIntegerArithmeticOperations.tcc"
#include "BigIntegerComparisons.tcc"
#include "Base.tcc"
#include "InvalidStringInputException.hh"
#include "ConversionFailedException.hh"
#include <algorithm>
#include <cmath>
#include <float.h>
#include <limits.h>
#include <sstream>


/*
 * TODO what about input in format "0010"? how does it work?
 */

BigInteger::BigInteger() : _negative(false)
{
    _digits.push_back(0);
}

BigInteger::BigInteger(std::vector<uint64_t> digits) : _digits(std::move(digits)), _negative(false)
{

}

/*
BigInteger::BigInteger(double value)
{
    std::cout<<"double constructor"<<std::endl;
    int exponent;
    double mantissa = frexp(value,&exponent);
    unsigned R = mantissa * UINT32_MAX;

    BigInteger temp((uint64_t) R);

    if(std::numeric_limits<double>::radix == 2)
        temp <<= exponent-(sizeof(unsigned)*CHAR_BIT);
    //else  TODO unreachable
      //  temp *= std::pow(exponent,(sizeof(unsigned)*CHAR_BIT));

    *this = temp;
}
*/

uint64_t power(uint64_t first, uint64_t second)
{
    uint64_t temp = 1;
    for(int i = 0; i < second; i++) {
        temp *= first;
    }

    return temp;
}

//TODO this probably can be optimized
BigInteger::BigInteger(std::string value, uint base)
{
    uint64_t smallerNumber = 0;
    int i = 0;

    if(base > 36 || base < 2)
        throw InvalidStringInputException("Invalid base of the number. Maximum base is 36 and minimum is 2.");

    if(value[0] == '-') {
        _negative = true;
        value = value.substr(1,value.size() - 1);
    }
    else {
        _negative = false;
    }

    std::size_t firstNonZero = value.find_first_not_of('0');

    if(firstNonZero != std::string::npos && firstNonZero != 0)
        value = value.substr(firstNonZero,value.size()-1);

    // Optimization by using more efficient operations on primitive type for as long as possible
    // Maximum possible base is 36 and uint64_t can hold up to 11 digits of base 36 number
    //TODO optimization for every possible base?
    while(i < value.size() && i <= 11)
    {
        int digit = charToNumber(value[value.size() - 1 - i]);

        if(digit >= base)
            throw InvalidStringInputException("Digit value is greater than base");

        smallerNumber += power(base,i)*digit;
        i++;
    }

    BigInteger bigInteger(smallerNumber);

    while(i < value.size())
    {
        BigInteger power(1);

        for(int j = 0; j < i; j++) {
            power = power * base;
        }


        int digit = charToNumber(value[value.size() - 1 - i]);

        if(digit >= base)
            throw InvalidStringInputException("Digit value is greater than base");

        BigInteger addition = power * digit;
        bigInteger += addition;

        i++;
    }

    bigInteger._negative = _negative;
    *this = bigInteger;
}

uint8_t BigInteger::charToNumber(char character)
{
    if(character > 47 && character < 58)
        return character - 48;
    else if(character > 64 && character < 91)
        return character - 55;
    else
        throw InvalidStringInputException("Character in input string is not a valid representation of numeric value: "
                                           + std::to_string(character));
}

BigInteger::BigInteger(const BigInteger& integer) : _digits(std::vector<uint64_t>(integer._digits)), _negative(integer._negative)
{

}

BigInteger::BigInteger(BigInteger&& integer) noexcept : _digits(std::move(integer._digits)), _negative(integer._negative)
{
    integer._digits = {0};
    integer._negative = false;

}

BigInteger::~BigInteger() = default;

BigInteger& BigInteger::operator=(const BigInteger& integer)
{
    _digits = integer._digits;
    _negative = integer._negative;
    return *this;
}

/*
BigInteger& BigInteger::operator=(const double& integer)
{
    *this = BigInteger(integer);
    return *this;
}
*/
//TODO can be optimized by custom swap?
BigInteger& BigInteger::operator=(BigInteger&& integer) noexcept
{
    _digits.clear();
    _digits = integer._digits;
    integer._digits = {0};

    _negative = integer._negative;
    integer._negative = false;

    return *this;
}

BigInteger::operator int8_t() const
{
    if(_digits.size() > 1 || _digits.empty() || *this > std::numeric_limits<int8_t>::max() ||
        *this < std::numeric_limits<int8_t>::min())
        throw ConversionFailedException("This BigInteger cannot be converted to int8_t");

    return _negative ? -_digits[0] : _digits[0];
}

BigInteger::operator int16_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<int16_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to int16_t");

    return _negative ? -_digits[0] : _digits[0];
}

BigInteger::operator int32_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<int32_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to int32_t");

    return _negative ? -_digits[0] : _digits[0];
}

BigInteger::operator int64_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<int64_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to int64_t");

    return _negative ? -_digits[0] : _digits[0];
}

BigInteger::operator uint8_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<uint8_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to uint8_t");

    return _digits[0];
}

BigInteger::operator uint16_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<uint16_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to uint16_t");

    return _digits[0];
}

BigInteger::operator uint32_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<uint32_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to uint32_t");

    return _digits[0];
}

BigInteger::operator uint64_t() const
{
    if(_digits.size() > 1 || _digits.empty() || _digits[0] > std::numeric_limits<uint64_t>::max())
        throw ConversionFailedException("This BigInteger cannot be converted to uint64_t");

    return _digits[0];
}

BigInteger::operator std::string() const
{
    return toString();
}

std::ostream& operator<<(std::ostream& stream, const BigInteger& integer)
{
    return stream << integer.toString();
}

std::string BigInteger::toString(int base) const
{
    Base readable(*this,base);
    return _negative ? "-" + readable.toString() : readable.toString();
}

std::istream& operator>>(std::istream& stream, BigInteger& integer)
{
    std::string number;
    stream >> number;
    integer = BigInteger(number,10);
    return stream;
}

