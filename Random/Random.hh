//
// Created by mrhowever on 08.11.19.
//

#ifndef BIGINTEGER_RANDOM_HH
#define BIGINTEGER_RANDOM_HH

#include <random>

namespace MC
{
    template<typename T, typename E = std::mt19937_64, typename G = std::random_device>
    class Random
    {
        static G _randomDevice;
        static E _engine;

        public:
        T next();
        T next(T, T);
        T next(T,bool);

        template<typename D>
        T next();

        template<typename D>
        T next(T, T);

        template<typename D>
        T next(T,bool);
    };
}

#endif //BIGINTEGER_RANDOM_HH
