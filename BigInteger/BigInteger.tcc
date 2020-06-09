//
// Created by mrhowever on 16.10.19.
//

#ifndef BIGINTEGER_BIGINTEGER_TCC
#define BIGINTEGER_BIGINTEGER_TCC


#include "BigInteger.hh"
#include <math.h>

template<typename T>
BigInteger::BigInteger(T integer)
{
    if constexpr (std::is_integral_v<T>) {
        _digits.push_back(integer < 0 ? -integer : integer);
        _negative = integer < 0;
    }
}

template<typename T>
BigInteger& BigInteger::operator=(T integer)
{
    if constexpr(std::is_integral_v<T>) {
        _digits.clear();
        _digits.push_back(integer < 0 ? -integer : integer);
        _negative = integer < 0;
        return *this;
    }
}
#endif //BIGINTEGER_BIGINTEGER_TCC
