//
// Created by mrhowever on 14.10.19.
//

#include "BigInteger.hh"

BigInteger abs(const BigInteger& integer)
{
    if(integer < 0)
        return -integer;

    return integer;
}