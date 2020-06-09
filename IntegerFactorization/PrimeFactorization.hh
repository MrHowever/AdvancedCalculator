//
// Created by mrhowever on 14.11.19.
//

#ifndef BIGINTEGER_PRIMEFACTORIZATION_HH
#define BIGINTEGER_PRIMEFACTORIZATION_HH

#include <list>
#include "../BigInteger/PrimeNumber/Prime.hh"

namespace MC
{
    namespace PF
    {
        template<typename T>
        std::list<T> naivePrimeFactorization(T input)
        {
            std::list<T> result;
            T currentDivisor = 2;

            //TODO move isPrime out of class, as a standalone function
            while(!MC::Prime<T>::isPrime(input)) {
                if(input % currentDivisor == 0) {
                    result.push_back(currentDivisor);
                    input /= currentDivisor;
                }
                else {
                    currentDivisor++;
                }
            }

            result.push_back(input);
            return result;
        }
    }
}
#endif //BIGINTEGER_PRIMEFACTORIZATION_HH
