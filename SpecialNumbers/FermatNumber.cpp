//
// Created by mrhowever on 21.11.19.
//

#include "FermatNumber.hh"
#include <cmath>
#include "../BasicOperations/BasicOperations.hh"
#include "InvalidParameterException.hh"
#include "../ArithmeticFunctions/ArithmeticFunctions.hh"

template<typename T>
MC::SN::FermatNumber<T>::FermatNumber(T value)
{
    if(BO::isPowOf2(value - 1) && BO::isPowOf2(std::round(std::log2(value - 1)))) {
        _value = value;
        _power = std::round(std::log2(std::round(std::log2(value - 1))));
    }
    else {
        throw InvalidParameterException("Value given is not a Fermat number");
    }
}

template<typename T>
inline MC::SN::FermatNumber<T>::operator T()
{
    return _value;
}

template<typename T>
inline T MC::SN::FermatNumber<T>::getPower()
{
    return _power;
}

template<typename T>
inline std::string MC::SN::FermatNumber<T>::print(bool preciseValue)
{
    return preciseValue ? _value : "2^(2^" + _power + ") + 1";
}

// Pepin primality test for Fermat numbers
template<typename T>
inline bool MC::SN::FermatNumber<T>::isPrime()
{
    return MO::modularPow(3, (_value - 1) / 2, _value) == -1;
}

template<typename T>
T MC::SN::FermatNumber<T>::next()
{
    return AF::pow((_value - 1), 2) + 1;
}