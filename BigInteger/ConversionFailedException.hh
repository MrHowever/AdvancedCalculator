//
// Created by mrhowever on 12.10.19.
//

#ifndef BIGINTEGER_CONVERSIONFAILEDEXCEPTION_HH
#define BIGINTEGER_CONVERSIONFAILEDEXCEPTION_HH

#include "BigIntegerException.hh"

class ConversionFailedException : public BigIntegerException
{
    std::string _message;

public:
    ConversionFailedException(std::string message) : _message(message), BigIntegerException(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};


#endif //BIGINTEGER_CONVERSIONFAILEDEXCEPTION_HH
