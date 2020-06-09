//
// Created by mrhowever on 14.10.19.
//

#ifndef BIGINTEGER_BIGINTEGEREMPTYEXCEPTION_HH
#define BIGINTEGER_BIGINTEGEREMPTYEXCEPTION_HH

#include "BigIntegerException.hh"

class BigIntegerEmptyException : public BigIntegerException
{
    std::string _message;

public:
    BigIntegerEmptyException(std::string message) : _message(message), BigIntegerException(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //BIGINTEGER_BIGINTEGEREMPTYEXCEPTION_HH
