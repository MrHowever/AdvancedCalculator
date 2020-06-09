//
// Created by mrhowever on 25.01.20.
//

#ifndef ARITHMETICFUNCTIONS_ARITHMETICFUNCTIONEXCEPTION_HH
#define ARITHMETICFUNCTIONS_ARITHMETICFUNCTIONEXCEPTION_HH

#include <stdexcept>
#include <string>

namespace MC::AF
{
    class ArithmeticFunctionException : public std::runtime_error {
        std::string _message;

    public:
        ArithmeticFunctionException(std::string message) : _message(message), std::runtime_error(message) {

        }

        virtual const char *what() const noexcept {
            return _message.c_str();
        }
    };
}
#endif //ARITHMETICFUNCTIONS_ARITHMETICFUNCTIONEXCEPTION_HH
