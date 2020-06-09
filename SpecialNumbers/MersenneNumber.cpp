//
// Created by mrhowever on 21.11.19.
//

#include <cmath>
#include "MersenneNumber.hh"
#include "../BasicOperations/BasicOperations.hh"
#include "InvalidParameterException.hh"
#include "../Prime/Prime.hh"
#include "../ModularOperations/ModularOperations.hh"

template<typename T>
MC::SN::MersenneNumber<T>::MersenneNumber(T value)
{
    //TODO technically std::round and log2 might not return perfect integer for HUGE power of 2 (big 64-bit integers )
    if(BO::isPowOf2(value + 1)) {
        _value = value;
        _power = std::round(log2(value+1));
    }
    else {
        throw InvalidParameterException("Value given is not a Mersenne number");
    }
}

template<typename T>
inline MC::SN::MersenneNumber<T>::operator T()
{
    return _value;
}

template<typename T>
inline T MC::SN::MersenneNumber<T>::getPower()
{
    return _power;
}

template<typename T>
inline std::string MC::SN::MersenneNumber<T>::print(bool preciseValue)
{
    return preciseValue ? _value : "2^" + _power + " - 1";
}

// Primality check for Mersenne number using Lucas-Lehmer test
template<typename T>
bool MC::SN::MersenneNumber<T>::isPrime()
{
    if(_power <= 2)
        return true;

    // For Mersenne number to be prime it's power has to be an odd prime number
    if(_power % 2 == 0 || !MC::Prime<T>::isPrime(_power))
        return false;

    //TODO swap for sequence
    T sequenceElement = 4;

    for(T i = 0; i < (_power - 2); i++) {
        sequenceElement = MO::modularSub(MO::modularMult(sequenceElement,sequenceElement, _value), 2,_value);
    }

    return sequenceElement == 0;
}

template<typename T>
T MC::SN::MersenneNumber<T>::next()
{
    return ((_value+1) * 2) - 1;
}