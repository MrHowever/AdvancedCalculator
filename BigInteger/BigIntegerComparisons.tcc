//
// Created by mrhowever on 16.10.19.
//

#ifndef BIGINTEGER_BIGINTEGERCOMPARISONS_TCC
#define BIGINTEGER_BIGINTEGERCOMPARISONS_TCC

#include "BigInteger.hh"
#include "BasicOperations/BasicOperations.hh"

template<typename T>
bool BigInteger::operator==(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if (_digits.size() > 1 || (_negative != (second.value < 0)))
            return false;

        return _digits[0] == second.value;
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator==(T first, const BigInteger& second)
{
    return second == first;
}

template<typename T>
bool BigInteger::operator!=(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if (_digits.size() > 1)
            return true;

        return _digits[0] != second.value ? true : _negative != (second < 0);
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator!=(T first, const BigInteger& second)
{
    return second != first;
}

template<typename T>
bool BigInteger::operator>(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if(_negative && second > 0)
            return false;

        if(second < 0 && !_negative)
            return true;

        if(_digits.size() > 1)
            return !_negative;

        if(_digits[0] == MC::BO::abs(second))
            return false;

        if(_digits[0] > MC::BO::abs(second)) {
            return !_negative;
        }
        else
            return _negative;
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator>(T first, const BigInteger& second)
{
    return second < first;
}

template<typename T>
bool BigInteger::operator<(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if (!_negative && second < 0)
            return false;

        if (second > 0 && _negative)
            return true;

        if(_digits.size() > 1)
            return _negative;

        if(_digits[0] == MC::BO::abs(second))
            return false;

        if (_digits[0] < MC::BO::abs(second))
            return !_negative;
        else
            return _negative;
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator<(T first, const BigInteger& second)
{
    return second > first;
}

template<typename T>
bool BigInteger::operator>=(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if (_negative && second > 0)
            return false;

        if (second < 0 && !_negative)
            return true;

        if(_digits.size() > 1)
            return !_negative;

        if(_digits[0] == MC::BO::abs(second))
            return true;

        if (_digits[0] >= MC::BO::abs(second))
            return !_negative;
        else
            return _negative;
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator>=(T first, const BigInteger& second)
{
    return second <= first;
}

template<typename T>
bool BigInteger::operator<=(T second) const
{
    if constexpr (std::is_integral_v<T>) {
        if (!_negative && second < 0)
            return false;

        if (second > 0 && _negative)
            return true;

        if(_digits[0] == MC::BO::abs(second))
            return true;

        if (_digits[0] <= MC::BO::abs(second))
            return !_negative;
        else
            return _negative;
    }
    else {
        BigInteger integer(second);
        return *this == integer;
    }
}

template<typename T>
bool operator<=(T first, const BigInteger& second)
{
    return second >= first;
}

#endif //BIGINTEGER_BIGINTEGERCOMPARISONS_TCC
