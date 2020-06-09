#include "library.h"
#include "PrimitiveRootException.hh"

#include <iostream>

uint64_t findNthPrimitiveRoot(uint64_t modulus, uint64_t order)
{
    for(uint64_t i = 2; i < modulus; i++) {
        if(MC::MO::modularPow(i,order,modulus) == 1)
            return i;
    }

    throw PrimitiveRootException("No primitive root of nth order");
}