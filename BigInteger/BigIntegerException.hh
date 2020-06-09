//
// Created by mrhowever on 07.10.19.
//

#ifndef BIGINTEGER_BIGINTEGEREXCEPTION_HH
#define BIGINTEGER_BIGINTEGEREXCEPTION_HH


#include <stdexcept>
#include <string>

class BigIntegerException : public std::runtime_error
{
    std::string _message;

public:
    BigIntegerException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};




#endif //BIGINTEGER_BIGINTEGEREXCEPTION_HH
