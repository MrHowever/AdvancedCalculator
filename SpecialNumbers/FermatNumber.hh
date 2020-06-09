//
// Created by mrhowever on 21.11.19.
//

#ifndef BIGINTEGER_FERMATNUMBER_HH
#define BIGINTEGER_FERMATNUMBER_HH

#include <string>

namespace MC::SN {
    template<typename T>
    class FermatNumber {
        const T _value;
        const T _power;

    public:
        FermatNumber(T);
        inline operator T();
        inline T getPower();
        inline std::string print(bool);
        inline bool isPrime();
        inline T next();
    };
}


#endif //BIGINTEGER_FERMATNUMBER_HH
