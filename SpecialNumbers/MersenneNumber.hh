//
// Created by mrhowever on 21.11.19.
//

#ifndef BIGINTEGER_MERSENNENUMBER_HH
#define BIGINTEGER_MERSENNENUMBER_HH

#include <string>

namespace MC::SN {
    template<typename T>
    class MersenneNumber {
        const T _value;
        const T _power;

    public:
        MersenneNumber(T);
        inline operator T();
        inline T getPower();
        inline std::string print(bool);
        bool isPrime();
        T next();
    };
}


#endif //BIGINTEGER_MERSENNENUMBER_HH
