//
// Created by mrhowever on 28.01.20.
//

#ifndef ARITHMETICFUNCTIONS_LOGARITHM_HH
#define ARITHMETICFUNCTIONS_LOGARITHM_HH

#include <cstdint>

namespace MC::AF
{
    template<typename T>
    class Logarithm {

        double __logarithm(T);
    public:
        double operator()(T,uint64_t = 10);
    };
}


#endif //ARITHMETICFUNCTIONS_LOGARITHM_HH
