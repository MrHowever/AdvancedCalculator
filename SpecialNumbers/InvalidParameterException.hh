//
// Created by mrhowever on 21.11.19.
//

#ifndef BIGINTEGER_INVALIDPARAMETEREXCEPTION_HH
#define BIGINTEGER_INVALIDPARAMETEREXCEPTION_HH


#include <stdexcept>

class InvalidParameterException : public std::runtime_error
{
    std::string _message;

public:
    InvalidParameterException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //BIGINTEGER_INVALIDPARAMETEREXCEPTION_HH
