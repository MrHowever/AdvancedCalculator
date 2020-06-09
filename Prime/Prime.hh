//
// Created by mrhowever on 08.11.19.
//

#ifndef BIGINTEGER_PRIME_HH
#define BIGINTEGER_PRIME_HH

namespace MC
{
    template<typename T>
    class Prime
    {
        T value;

        T generatePrime(bool = false);
        T generatePrime(T,T,bool = false);
        T generatePrime(T,bool,bool = false);

    public:
        Prime();
        explicit Prime(T);
        Prime(T,T);
        explicit Prime(T,bool = true);
        Prime(const Prime&);
        Prime(Prime&&) noexcept;

        Prime& operator=(T);
        Prime& operator=(const Prime&);
        Prime& operator=(Prime&&) noexcept;

        operator T();

        //TODO move this outside class
        static bool isPrime(T);
        static bool millerRabin(T);
        static bool checkWitness(T,T,T);
    };
}

#endif //BIGINTEGER_PRIME_HH
