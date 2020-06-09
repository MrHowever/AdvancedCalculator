//
// Created by mrhowever on 28.01.20.
//

#include "../include/Logarithm.hh"

namespace MC::AF
{
    template<typename T>
    double Logarithm<T>::operator()(T value, uint64_t base)
    {
        if(base != 10) {
            return __logarithm(value) / __logarithm(base);
        }

        return __logarithm(value);
    }

    // Base 10 logarithm subroutine
    template<typename T>
    double Logarithm<T>::__logarithm(T value)
    {

    }
}
