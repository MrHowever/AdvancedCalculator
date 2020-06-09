//
// Created by mrhowever on 12.11.19.
//

#ifndef BIGINTEGER_BASICOPERATIONS_HH
#define BIGINTEGER_BASICOPERATIONS_HH

#include <limits>
#include <algorithm>
#include <cmath>
#include "BasicOperationsException.hh"
#include <Comparable.hh>
#include <Bounded.hh>
#include <CustomTypeTraits.hh>

namespace MC::BO
{
    template<typename T>
    T max(T a, T b)
    {
        if constexpr (std::is_arithmetic_v<T> || std::is_base_of_v<MC::Comparable<T>, T>) {
            return a >= b ? a : b;
        } else {
            throw BasicOperationsException("Cannot compare non-arithmetic or non-comparable object");
        }
    }

    template<typename T>
    T max()
    {
        if constexpr(std::is_base_of_v<MC::Bounded<T>, T>) {
            return T::max();
        } else if constexpr(std::is_arithmetic_v<T>) {
            return std::numeric_limits<T>::max();
        } else {
            throw BasicOperationsException("Cannot get value from non-arithmetic or unbounded object");
        }
    }

    template<typename T>
    auto max(T container)
    {
        if constexpr(MC::is_container<T>::value) {
            return *std::max_element(container.begin(), container.end());
        } else {
            throw BasicOperationsException("Single parameter max function is defined only for containers");
        }
    }

    template<typename T>
    T min()
    {
        if constexpr(std::is_base_of_v<MC::Bounded<T>, T>) {
            return T::min();
        } else if constexpr(std::is_arithmetic_v<T>) {
            return std::numeric_limits<T>::min();
        } else {
            throw BasicOperationsException("Cannot get value from non-arithmetic or unbounded object");
        }
    }

    template<typename T>
    auto min(T container)
    {
        if constexpr(MC::is_container<T>::value) {
            return *std::min_element(container.begin(), container.end());
        } else {
            throw BasicOperationsException("Single parameter min function is defined only for containers");
        }
    }

    template<typename T>
    T min(T a, T b)
    {
        if constexpr (std::is_arithmetic_v<T> || std::is_base_of_v<Comparable<T>, T>) {
            return a <= b ? a : b;
        } else {
            throw BasicOperationsException("Cannot compare non-arithmetic or non-comparable object");
        }
    }

    //TODO what about uneven ranges for example -127:128?
    template<typename T>
    T abs(T value)
    {
        if constexpr (std::is_unsigned_v<T>)
            return value;
        else
            return value < 0 ? -value : value;
    }

    template<typename T>
    T gcd(T a, T b)
    {

        if (b == 0)
            return a;

        return gcd(b, a % b);
    }

    template<typename G>
    auto gcd(const G& input)
    {
        if constexpr(MC::is_container<G>::value) {
            auto result = input.front();

            //Start at second position
            auto it = input.begin();
            for (it++; it != input.end(); it++) {
                result = gcd(result, *it);
            }

            return result;
        } else {
            throw BasicOperationsException(
                    "Used GCD function for containers on non container type. Did u mean gcd(a,b)?");
        }
    }

    //TODO check different algorithms
    template<typename T>
    T lcm(T a, T b)
    {
        if (a == 0 && b == 0)
            return 0;

        return BO::abs(a * b) / gcd(a, b);
    }

    template<typename T>
    inline bool isPowOf2(T value)
    {
        return (value & (value - 1)) == 0;
    }

    //TODO check if iterating isnt faster or when/where
    template<typename T>
    T binaryLength(T val)
    {
        if (!val)
            return 1;

        return std::floor(std::log2(val)) + 1;
    }

    template<typename T>
    T iterativeBinaryLength(T val)
    {
        T length = 1;

        while (val) {
            val >>= 1;
            length++;
        }

        return length;
    }

    template<typename ...Types>
    struct Range {
        Range() = default;

        Range(const Range&) = delete;

        Range(Range&&) = delete;

        Range& operator=(const Range&) = delete;

    public:
        template<typename V>
        inline constexpr bool includes(V val) const
        {
            return false;
        }
    };

    template<typename T, typename P, typename ...Types>
    struct Range<T, P, Types...> {
        const T _lowerBound;
        const P _upperBound;
        const Range<Types...> _nextRange;

    public:
        Range() = delete;

        Range(const Range&) = delete;

        Range(Range&&) = delete;

        Range& operator=(const Range&) = delete;

        explicit Range(T lowerBound, P upperBound, Types... bounds) : _lowerBound(lowerBound),
                                                                      _upperBound(upperBound),
                                                                      _nextRange(bounds...)
        {}

        template<typename V>
        inline bool includes(V val) const
        {
            return (val > _lowerBound && val < _upperBound) or _nextRange.includes(val);
        }
    };
}

#endif //BIGINTEGER_BASICOPERATIONS_HH
