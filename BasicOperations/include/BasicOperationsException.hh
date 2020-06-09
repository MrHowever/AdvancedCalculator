//
// Created by mrhowever on 13.11.19.
//

#ifndef BIGINTEGER_BASICOPERATIONSEXCEPTION_HH
#define BIGINTEGER_BASICOPERATIONSEXCEPTION_HH


#include <stdexcept>

class BasicOperationsException : public std::runtime_error
{
    std::string _message;

public:
    BasicOperationsException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //BIGINTEGER_BASICOPERATIONSEXCEPTION_HH
