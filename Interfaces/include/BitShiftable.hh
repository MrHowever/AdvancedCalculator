//
// Created by mrhowever on 14.11.19.
//

#ifndef BIGINTEGER_BITSHIFTABLE_HH
#define BIGINTEGER_BITSHIFTABLE_HH

#include <cstdint>

namespace MC {
    template<typename T>
    class BitShiftable {
        virtual T operator>>(const T&) const = 0;
        virtual T& operator>>=(const T&) = 0;
        virtual T operator<<(const T&) const = 0;
        virtual T& operator<<=(const T&) = 0;
        virtual T operator>>(uint64_t) const = 0;
        virtual T& operator>>=(uint64_t) = 0;
        virtual T operator<<(uint64_t) const = 0;
        virtual T& operator<<=(uint64_t) = 0;
    };
}

#endif //BIGINTEGER_BITSHIFTABLE_HH
