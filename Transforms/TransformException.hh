//
// Created by mrhowever on 18.11.19.
//

#ifndef BIGINTEGER_TRANSFORMEXCEPTION_HH
#define BIGINTEGER_TRANSFORMEXCEPTION_HH


class TransformException : public std::runtime_error
{
    std::string _message;

public:
    TransformException(std::string message) : _message(message), std::runtime_error(message)
    {

    }

    virtual const char* what() const noexcept
    {
        return _message.c_str();
    }
};

#endif //BIGINTEGER_TRANSFORMEXCEPTION_HH
