//
// Created by mrhowever on 08.11.19.
//

#include <type_traits>
#include "Prime.hh"
#include "../BigInteger/Random/Random.cpp"
#include "../BigInteger/Random/Random.hh"
#include "PrimeException.hh"
#include "../ModularOperations/ModularOperations.hh"

//TODO make non arithmetic T illegal

template<typename T>
MC::Prime<T>::Prime()
{
    value = generatePrime();
}

template<typename T>
MC::Prime<T>::Prime(T prime)
{
    if(isPrime(prime)) {
        value = prime;
    }
    else {
        throw PrimeException("Trying to create Prime object with non-prime value");
    }
}

template<typename T>
MC::Prime<T>::Prime(T min, T max)
{
    if(min == 0 || max == 0 || min > max) {
        throw PrimeException("Invalid min and max parameters for Prime construction");
    }

    value = generatePrime(min,max);
}

template<typename T>
MC::Prime<T>::Prime(T boundary, bool upper)
{
    value = generatePrime(boundary,upper);
}

template<typename T>
MC::Prime<T>::Prime(const Prime& prime) : value(prime.value)
{
}

template<typename T>
MC::Prime<T>::Prime(Prime&& prime) noexcept : value(prime.value)
{
    if constexpr(!std::is_object_v<T>) {
        prime.value = 0;
    }
    else {
        prime.value = T();
    }
}

template<typename T>
MC::Prime<T>& MC::Prime<T>::operator=(T prime)
{
    if(!isPrime(prime)) {
        throw PrimeException("Trying to create Prime object with non-prime value");
    }

    value = prime;
    return *this;
}

template<typename T>
MC::Prime<T>& MC::Prime<T>::operator=(const Prime& prime)
{
    value = prime.value;
    return *this;
}

template<typename T>
MC::Prime<T>& MC::Prime<T>::operator=(Prime&& prime) noexcept
{
    if constexpr(!std::is_object_v<T>) {
        prime.value = 0;
        return *this;
    }
    else {
        prime.value = T();
        return *this;
    }
}

template<typename T>
T MC::Prime<T>::generatePrime(bool smallestPossible)
{
    Random<T> random;
    T number = smallestPossible ? BO::min<T>() : random.next();

    do {
        number++;
    } while (!isPrime(number));

    return number;
}

template<typename T>
T MC::Prime<T>::generatePrime(T min, T max, bool smallestPossible)
{
    Random<T> random;
    T number = smallestPossible ? min : random.next(min,max);

    do {
        number++;
    } while (!isPrime(number));

    return number;
}

template<typename T>
T MC::Prime<T>::generatePrime(T min, bool biggerThan, bool smallestPossible)
{
    Random<T> random;
    T number = smallestPossible && biggerThan ? min : random.next(min,biggerThan);

    do {
        number++;
    } while (!isPrime(number));

    return number;
}

template<typename T>
bool MC::Prime<T>::checkWitness(T oddComp, T number, T power)
{
    Random<T> random;
    T random_num = (random.next()%(number-4))+2;
    T temp = MO::modularPow(random_num,oddComp,number);

    if(temp == 1 || temp == number-1)
        return true;

    while(temp != (number-1) && oddComp != (number-1))
    {
        temp = (temp*temp) % number;
        oddComp *= 2;
    }

    return temp == number-1;
}

template<typename T>
bool MC::Prime<T>::millerRabin(T number)
{
    T decomp = 0;
    T power = 0, odd_comp = 0;

    //If number is even return false
    if(number % 2 == 0 && number != 2)
        return false;

    //Number is an odd number, decomp is an even number
    decomp = number - 1;
    odd_comp = decomp;

    //Find the biggest power of 2 that satisfies the equation 2^u*r = number
    while(odd_comp % 2 == 0)
    {
        power++;
        odd_comp /= 2;
    }

    //odd_comp is now an odd number
    //Check 10 times if odd_comp is a witness to number's primality, if it is
    //return true. This algorithm is probabilistic, more loops means more
    //accurate result
    for(int i = 0; i < 10; i++)
    {
        if(!checkWitness(odd_comp,number,power))
            return false;
    }

    return true;
}

template<typename T>
bool MC::Prime<T>::isPrime(T number)
{
    if(number < 3 && number > 0)
        return true;

    return millerRabin(number);
}

template<typename T>
MC::Prime<T>::operator T()
{
    return value;
}

