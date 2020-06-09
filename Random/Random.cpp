//
// Created by mrhowever on 08.11.19.
//

#include <type_traits>
#include "Random.hh"
#include "Randomizable.hh"
#include "../BasicOperations/BasicOperations.hh"

template<typename T, typename E, typename G>
G MC::Random<T, E, G>::_randomDevice = G();

template<typename T, typename E, typename G>
E MC::Random<T, E, G>::_engine = E(_randomDevice());

template<typename T, typename E, typename G>
T MC::Random<T, E, G>::next()
{
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distribution;
        return distribution(_engine);
    }
    else if constexpr(std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> distribution;
        return distribution(_engine);
    }
    else if constexpr (std::is_base_of_v<Randomizable<T>,T>) {
        return T::getRandom(*this);
    }
    else {
        throw RandomizerException("Template type is not arithmetic or Randomizable");
    }
}

template<typename T, typename E, typename G>
T MC::Random<T, E, G>::next(T min, T max)
{
    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distribution(min,max);
        return distribution(_engine);
    }
    else if constexpr(std::is_floating_point_v<T>) {
        std::uniform_real_distribution<T> distribution(min,max);
        return distribution(_engine);
    }
    else if constexpr (std::is_base_of_v<Randomizable<T>,T>) {
        return T::getRandom(min,max,*this);
    }
    else {
        throw RandomizerException("Template type is not arithmetic or Randomizable");
    }
}

template<typename T, typename E, typename G>
T MC::Random<T, E, G>::next(T bound, bool biggerThenBound)
{
    if constexpr (std::is_integral_v<T>) {
        T upperBound = !biggerThenBound ? bound : BO::max<T>();
        T lowerBound = biggerThenBound ? bound : BO::min<T>();

        std::uniform_int_distribution<T> distribution(lowerBound,upperBound);
        return distribution(_engine);
    }
    else if constexpr(std::is_floating_point_v<T>) {
        T upperBound = !biggerThenBound ? bound : BO::max<T>();
        T lowerBound = biggerThenBound ? bound : BO::min<T>();

        std::uniform_real_distribution<T> distribution(lowerBound,upperBound);
        return distribution(_engine);
    }
    else if constexpr (std::is_base_of_v<Randomizable<T>,T>) {
        return T::getRandom(bound,biggerThenBound,*this);
    }
    else {
        throw RandomizerException("Template type is not arithmetic or Randomizable");
    }
}

//TODO pass the distribution to getRandom method

template<typename T, typename E, typename G>
template<typename D>
T MC::Random<T, E, G>::next()
{
    D distribution;
    return distribution(_engine);
}

template<typename T, typename E, typename G>
template<typename D>
T MC::Random<T, E, G>::next(T min, T max)
{
    D distribution(min,max);
    return distribution(_engine);
}

template<typename T, typename E, typename G>
template<typename D>
T MC::Random<T, E, G>::next(T bound, bool biggerThenBound)
{
    T upperBound = !biggerThenBound ? bound : BO::max<T>();
    T lowerBound = biggerThenBound ? bound : BO::min<T>();

    D distribution(lowerBound,upperBound);
    return distribution(_engine);
}