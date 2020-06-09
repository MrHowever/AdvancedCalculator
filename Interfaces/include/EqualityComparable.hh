//
// Created by mrhowever on 16.02.2020.
//

#ifndef INTERFACES_EQUALITYCOMPARABLE_HH
#define INTERFACES_EQUALITYCOMPARABLE_HH

namespace MC {
    template<typename T>
    class EqualityComparable {
    public:
        virtual bool operator==(const T &) const = 0;
        virtual bool operator!=(const T &) const = 0;
    };
}

#endif //INTERFACES_EQUALITYCOMPARABLE_HH
