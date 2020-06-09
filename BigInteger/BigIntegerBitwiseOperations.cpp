//
// Created by mrhowever on 14.10.19.
//

#include "BigInteger.hh"
#include "BigIntegerEmptyException.hh"
#include "BigIntegerArithmeticOperations.tcc"

BigInteger BigInteger::operator&(const BigInteger& integer) const
{
    BigInteger result(_digits.size() <= integer._digits.size() ? *this : integer);
    int smallerSize = std::min(_digits.size(), integer._digits.size());

    for(int i = 0; i < smallerSize; i++) {
        if(smallerSize == _digits.size())
            result._digits[i] &= integer._digits[i];
        else
            result._digits[i] &= _digits[i];
    }

    return result;
}

BigInteger& BigInteger::operator&=(const BigInteger& integer)
{
    *this = *this & integer;
    return *this;
}

BigInteger BigInteger::operator|(const BigInteger& integer) const
{
    BigInteger result(_digits.size() >= integer._digits.size() ? *this : integer);
    int smallerSize = std::min(_digits.size(), integer._digits.size());

    for(int i = 0; i < smallerSize; i++) {
        if(smallerSize == integer._digits.size())
            result._digits[i] |= integer._digits[i];
        else
            result._digits[i] |= _digits[i];
    }

    return result;
}

BigInteger& BigInteger::operator|=(const BigInteger& integer)
{
   *this = *this | integer;
   return *this;
}

BigInteger BigInteger::operator~() const
{
    BigInteger result(*this);

    for(auto& digit : result._digits) {
        digit = ~digit;
    }

    while(_digits.back() == 0)
        result._digits.pop_back();

    return result;
}

BigInteger BigInteger::operator^(const BigInteger& integer) const
{
    BigInteger result(_digits.size() >= integer._digits.size() ? *this : integer);
    int smallerSize = std::min(_digits.size(), integer._digits.size());

    for(int i = 0; i < smallerSize; i++) {
        if(smallerSize == integer._digits.size())
            result._digits[i] ^= integer._digits[i];
        else
            result._digits[i] ^= _digits[i];
    }

    return result;
}

BigInteger& BigInteger::operator^=(const BigInteger& integer)
{
    *this = *this ^ integer;
    return *this;
}

BigInteger BigInteger::operator<<(uint64_t integer) const
{
    BigInteger result(*this);
    uint64_t shift = integer;

    do {
        uint64_t overflow = 0;
        uint64_t nextOverflow = 0;

        for (int i = 0; i < _digits.size(); i++) {
            if(shift >= 64) {
                nextOverflow = result._digits[i];
                result._digits[i] = overflow;
                overflow = nextOverflow;
            }
            else {
                nextOverflow = shift > 0 && _digits[i] != 0 ? _digits[i] >> (64 - shift) : 0;  //If shift equals uint bit size it overflows= shift > 0 && _digits[i] != 0 ? _digits[i] >> (64 - shift) : 0;  //If shift equals uint bit size it overflows
                result._digits[i] <<= shift;
                result._digits[i] |= overflow;
                overflow = nextOverflow;
            }
        }

        if(shift >= 64)
            shift -= 64;

    } while(shift > 64);

    while(result._digits.back() == 0 && result._digits.size() > 1) {
        result._digits.pop_back();
    }

    return result;
}

BigInteger BigInteger::shiftLeft(uint64_t integer) const
{
    BigInteger result(*this);
    uint64_t shift = integer;

    do {
        uint64_t overflow = 0;
        uint64_t nextOverflow = 0;

        for (int i = 0; i < result._digits.size(); i++) {
            if(shift >= 64) {
                nextOverflow = result._digits[i];
                result._digits[i] = overflow;
                overflow = nextOverflow;
            }
            else {
                nextOverflow = shift > 0 && _digits[i] != 0 ? _digits[i] >> (64 - shift) : 0;  //If shift equals uint bit size it overflows= shift > 0 && _digits[i] != 0 ? _digits[i] >> (64 - shift) : 0;  //If shift equals uint bit size it overflows
                result._digits[i] <<= shift;
                result._digits[i] |= overflow;
                overflow = nextOverflow;
            }
        }

        if(overflow) {
            result._digits.push_back(overflow);
        }

        if(shift >= 64)
            shift -= 64;

    } while(shift >= 64);

    while(result._digits.back() == 0 && result._digits.size() > 1) {
        result._digits.pop_back();
    }

    return result;
}

BigInteger& BigInteger::operator<<=(uint64_t integer)
{
    uint64_t shift = integer;

    do {
        uint64_t nextOverflow = 0;
        uint64_t overflow = 0;

        for (int i = 0; i < _digits.size(); i++) {
            if(shift >= 64) {
                nextOverflow = _digits[i];
                _digits[i] = overflow;
                overflow = nextOverflow;
            }
            else {
                nextOverflow = integer > 0 ? _digits[i] >> (64 - integer) : 0;
                _digits[i] <<= shift;
                _digits[i] |= overflow;
                overflow = nextOverflow;
            }
        }

        if(shift >= 64)
            shift -= 64;

    } while(shift > 64);

    while(_digits.back() == 0 && _digits.size() > 1) {
        _digits.pop_back();
    }

    return *this;
}

BigInteger BigInteger::operator>>(uint64_t integer) const
{
    BigInteger result(*this);
    uint64_t shift = integer;

    do {
        uint64_t overflow = 0;
        uint64_t nextOverflow = 0;

        for (int i = _digits.size() - 1; i >= 0; i--) {
            if(shift >= 64) {
                nextOverflow = result._digits[i];
                result._digits[i] = overflow;
                overflow = nextOverflow;
            }
            else {
                nextOverflow = integer > 0 ? _digits[i] << (64 - integer) : 0;  //If shift equals uint bit size it overflows
                result._digits[i] >>= shift;
                result._digits[i] |= overflow;
                overflow = nextOverflow;
            }
        }

        if(shift >= 64)
            shift -= 64;

    } while(shift > 64);

    while(result._digits.back() == 0 && result._digits.size() > 1) {
        result._digits.pop_back();
    }

    return result;
}

BigInteger& BigInteger::operator>>=(uint64_t integer)
{
    uint64_t shift = integer;

    do {
        uint64_t nextOverflow = 0;
        uint64_t overflow = 0;

        for (int i = _digits.size() - 1; i >= 0; i--) {
            if(shift >= 64) {
                nextOverflow = _digits[i];
                _digits[i] = overflow;
                overflow = nextOverflow;
            }
            else {
                nextOverflow = integer > 0 ? _digits[i] << (64 - integer) : 0;
                _digits[i] >>= shift;
                _digits[i] |= overflow;
                overflow = nextOverflow;
            }
        }

        if(shift >= 64)
            shift -= 64;

    } while(shift > 64);

    while(_digits.back() == 0 && _digits.size() > 1) {
        _digits.pop_back();
    }

    return *this;
}

BigInteger BigInteger::operator<<(const BigInteger& integer) const
{
    BigInteger integerCopy(integer);
    uint64_t remainder = (uint64_t) integer % 64;
    BigInteger result(*this);

    while(integerCopy >= 64) {
        result <<= 64;
        integerCopy -= 64;
    }

    return result <<= remainder;
}

BigInteger BigInteger::shiftLeft(const BigInteger& integer) const
{
    BigInteger integerCopy(integer);
    uint64_t remainder = (uint64_t) integer % 64;
    BigInteger result(*this);

    while(integerCopy >= 64) {
        result.shiftLeft(64);
        integerCopy -= 64;
    }

    return result.shiftLeft(remainder);
}

BigInteger& BigInteger::operator<<=(const BigInteger& integer)
{
    BigInteger integerCopy(integer);
    uint64_t remainder = (uint64_t) integer % 64;

    while(integerCopy >= 64) {
        *this <<= 64;
        integerCopy -= 64;
    }

    return *this <<= remainder;
}

BigInteger BigInteger::operator>>(const BigInteger& integer) const
{
    BigInteger integerCopy(integer);
    uint64_t remainder = (uint64_t) integer % 64;
    BigInteger result(*this);

    while(integerCopy >= 64) {
        result >>= 64;
        integerCopy -= 64;
    }

    return result >>= remainder;
}

BigInteger& BigInteger::operator>>=(const BigInteger& integer)
{
    BigInteger integerCopy(integer);
    uint64_t remainder = (uint64_t) integer % 64;

    while(integerCopy >= 64) {
        *this >>= 64;
        integerCopy -= 64;
    }

    return *this >>= remainder;}

BigInteger BigInteger::operator&(uint64_t integer) const
{
    if(_digits.empty())
        throw BigIntegerEmptyException("Operator & used on empty BigInteger");

    BigInteger result(_digits[0] & integer);
    result._negative = false;

    return result;
}

BigInteger& BigInteger::operator&=(uint64_t integer)
{
    *this = *this & integer;
    return *this;
}

BigInteger BigInteger::operator|(uint64_t integer) const
{
    if(_digits.empty())
        throw BigIntegerEmptyException("Operator | used on empty BigInteger");

    BigInteger result(_digits[0] | integer);
    result._negative = false;

    return result;
}

BigInteger& BigInteger::operator|=(uint64_t integer)
{
    *this = *this | integer;
    return *this;
}

BigInteger BigInteger::operator^(uint64_t integer) const
{
    if(_digits.empty())
        throw BigIntegerEmptyException("Operator ^ used on empty BigInteger");

    BigInteger result(_digits[0] ^ integer);
    result._negative = false;

    return result;
}

BigInteger& BigInteger::operator^=(uint64_t integer)
{
    *this = *this ^ integer;
    return *this;
}

uint64_t operator&(const uint64_t& first, const BigInteger& second)
{
    return (uint64_t) second & first;
}

uint64_t& operator&=(uint64_t& first, const BigInteger& second)
{
    first = (uint64_t) second & first;
    return first;
}

uint64_t operator|(const uint64_t& first, const BigInteger& second)
{
    return (uint64_t) second | first;
}

uint64_t& operator|=(uint64_t& first, const BigInteger& second)
{
    first = (uint64_t) second | first;
    return first;
}

uint64_t operator<<(const uint64_t& first, const BigInteger& second)
{
    return first << (uint64_t) second;
}

uint64_t& operator<<=(uint64_t& first, const BigInteger& second)
{
    first <<= (uint64_t) second;
    return first;
}

uint64_t operator>>(const uint64_t& first, const BigInteger& second)
{
    return first >> (uint64_t) second;
}

uint64_t& operator>>=(uint64_t& first, const BigInteger& second)
{
    first >>= (uint64_t) second;
    return first;
}

uint64_t operator^(const uint64_t& first, const BigInteger& second)
{
    return (uint64_t) second ^ first;
}

uint64_t& operator^=(uint64_t& first, const BigInteger& second)
{
    first = (uint64_t) second ^ first;
    return first;
}

