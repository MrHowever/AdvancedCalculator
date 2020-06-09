//
// Created by mrhowever on 13.11.19.
//

#ifndef BIGINTEGER_COMPARABLE_HH
#define BIGINTEGER_COMPARABLE_HH

#include "EqualityComparable.hh"

namespace MC {
    template<typename T>
    class Comparable : public EqualityComparable<T> {
        virtual bool operator>(const T &) const = 0;
        virtual bool operator>=(const T &) const = 0;
        virtual bool operator<(const T &) const = 0;
        virtual bool operator<=(const T &) const = 0;
    };
}
#endif //BIGINTEGER_COMPARABLE_HH
