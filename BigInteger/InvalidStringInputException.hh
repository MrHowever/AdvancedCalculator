//
// Created by mrhowever on 07.10.19.
//

#ifndef BIGINTEGER_INVALIDSTRINGINPUTEXCEPTION_HH
#define BIGINTEGER_INVALIDSTRINGINPUTEXCEPTION_HH


#include "BigIntegerException.hh"

class InvalidStringInputException : public BigIntegerException
{
    std::string _message;

public:
    InvalidStringInputException(std::string message) : _message(message), BigIntegerException(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};


#endif //BIGINTEGER_INVALIDSTRINGINPUTEXCEPTION_HH
