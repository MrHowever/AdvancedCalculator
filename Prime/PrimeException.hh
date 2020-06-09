//
// Created by mrhowever on 11.11.19.
//

#ifndef BIGINTEGER_PRIMEEXCEPTION_HH
#define BIGINTEGER_PRIMEEXCEPTION_HH

#include <stdexcept>

class PrimeException : public std::runtime_error
{
    std::string _message;

public:
    PrimeException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //BIGINTEGER_PRIMEEXCEPTION_HH
