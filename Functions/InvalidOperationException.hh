//
// Created by mrhowever on 29.01.20.
//

#ifndef FUNCTIONS_INVALIDOPERATIONEXCEPTION_HH
#define FUNCTIONS_INVALIDOPERATIONEXCEPTION_HH

#include <stdexcept>

class InvalidOperationException : public std::runtime_error
{
    std::string _message;

public:
    InvalidOperationException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //FUNCTIONS_INVALIDOPERATIONEXCEPTION_HH
