//
// Created by mrhowever on 14.10.19.
//

#include "BigInteger.hh"

bool BigInteger::operator==(const BigInteger& integer) const
{
    if(_negative != integer._negative || _digits.size() != integer._digits.size())
        return false;

    for(int i = 0; i < _digits.size(); i++) {
        if(_digits[i] != integer._digits[i])
            return false;
    }

    return true;
}

bool BigInteger::operator!=(const BigInteger& integer) const
{
    return !(*this == integer);
}

bool BigInteger::operator>(const BigInteger& integer) const
{
    if(!_negative && integer._negative)
        return true;

    if(_negative && !integer._negative)
        return false;

    if(_digits.size() > integer._digits.size())
        return !_negative;

    if(_digits.size() < integer._digits.size())
        return _negative;

    for(int i = _digits.size() - 1; i >= 0 ; i--) {
        if(_digits[i] > integer._digits[i])
            return !_negative;
        if(_digits[i] < integer._digits[i])
            return _negative;
    }

    return false;
}

bool BigInteger::operator<(const BigInteger& integer) const
{
    if(!_negative && integer._negative)
        return false;

    if(_negative && !integer._negative)
        return true;

    if(_digits.size() > integer._digits.size())
        return _negative;

    if(_digits.size() < integer._digits.size())
        return !_negative;

    for(int i = _digits.size() - 1; i >= 0 ; i--) {
        if(_digits[i] < integer._digits[i])
            return !_negative;
        if(_digits[i] > integer._digits[i])
            return _negative;
    }

    return false;
}

bool BigInteger::operator>=(const BigInteger& integer) const
{
    if(!_negative && integer._negative)
        return true;

    if(_negative && !integer._negative)
        return false;

    if(_digits.size() > integer._digits.size())
        return !_negative;

    if(_digits.size() < integer._digits.size())
        return _negative;

    for(int i = _digits.size() - 1; i >= 0 ; i--) {
        if(_digits[i] > integer._digits[i])
            return !_negative;
        if(_digits[i] < integer._digits[i])
            return _negative;
    }

    return true;
}

bool BigInteger::operator<=(const BigInteger& integer) const
{
    if(!_negative && integer._negative)
        return false;

    if(_negative && !integer._negative)
        return true;

    if(_digits.size() > integer._digits.size())
        return _negative;

    if(_digits.size() < integer._digits.size())
        return !_negative;

    for(int i = _digits.size() - 1; i >= 0 ; i--) {
        if(_digits[i] < integer._digits[i])
            return !_negative;
        if(_digits[i] > integer._digits[i])
            return _negative;
    }

    return true;
}
