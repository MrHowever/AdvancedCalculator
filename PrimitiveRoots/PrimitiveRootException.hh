//
// Created by mrhowever on 24.01.20.
//

#ifndef PRIMITIVEROOTS_PRIMITIVEROOTEXCEPTION_HH
#define PRIMITIVEROOTS_PRIMITIVEROOTEXCEPTION_HH

#include <stdexcept>
#include <string>

class PrimitiveRootException : public std::runtime_error
{
    std::string _message;

public:
    PrimitiveRootException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //PRIMITIVEROOTS_PRIMITIVEROOTEXCEPTION_HH
