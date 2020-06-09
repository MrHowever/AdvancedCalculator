//
// Created by mrhowever on 08.11.19.
//

#ifndef BIGINTEGER_RANDOMIZABLE_HH
#define BIGINTEGER_RANDOMIZABLE_HH

// CRTP pattern

#include "../BigInteger/Interfaces/Bounded.hh"
#include "Random.hh"
#include "RandomizerException.hh"

namespace MC {
    template<class T>
    class Randomizable {
    public:
        template<typename E, typename G>
        static T getRandom(const E &engine, const G &generator) {
            if constexpr (std::is_base_of_v<Bounded<T>, T>) {
                return T::random(engine, generator);
            } else {
                throw RandomizerException("Cannot use unbounded random generator on type with no bounds");
            }
        }

        template<typename E, typename G>
        static T getRandom(T min, T max, const E &engine, const G &generator) {
            return T::random(min, max, engine, generator);
        }

        template<typename E, typename G>
        static T getRandom(T bound, bool upper, const E &engine, const G &generator) {
            if constexpr (std::is_base_of_v<Bounded<T>, T>) {
                if (upper)
                    return T::random(bound, T::max(), engine, generator);
                else
                    return T::random(T::min(), bound, engine, generator);
            } else {
                throw RandomizerException("Cannot use unbounded random generator on type with no bounds");
            }
        }

        template<typename E, typename G, typename D>
        static T getRandom(const E &engine, const G &generator, const D &distribution) {
            if constexpr (std::is_base_of_v<Bounded<T>, T>) {
                return T::random(engine, generator, distribution);
            } else {
                throw RandomizerException("Cannot use unbounded random generator on type with no bounds");
            }
        }

        template<typename E, typename G, typename D>
        static T getRandom(T min, T max, const E &engine, const G &generator, const D &distribution) {
            return T::random(min, max, engine, generator, distribution);
        }

        template<typename E, typename G, typename D>
        static T getRandom(T bound, bool upper, const E &engine, const G &generator, const D &distribution) {
            if constexpr (std::is_base_of_v<Bounded<T>, T>) {
                if (upper)
                    return T::random(bound, T::max(), engine, generator, distribution);
                else
                    return T::random(T::min(), bound, engine, generator, distribution);
            } else {
                throw RandomizerException("Cannot use unbounded random generator on type with no bounds");
            }
        }
    };
}
#endif //BIGINTEGER_RANDOMIZABLE_HH
