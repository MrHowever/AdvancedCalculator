//
// Created by mrhowever on 11.11.19.
//

#ifndef BIGINTEGER_RANDOMIZEREXCEPTION_HH
#define BIGINTEGER_RANDOMIZEREXCEPTION_HH

#include <stdexcept>

class RandomizerException : public std::runtime_error
{
    std::string _message;

public:
    RandomizerException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};


#endif //BIGINTEGER_RANDOMIZEREXCEPTION_HH
