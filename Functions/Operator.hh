#ifndef FUNCTIONS_OPERATOR_HH
#define FUNCTIONS_OPERATOR_HH

#include "ArithmeticObject.hh"
#include "Typedefs.hh"
#include <string>

namespace MC::FN
{
    class Sum;
    class Multiplication;
    class Division;
    class Variable;
    class Logarithm;

    class Operator : public ArithmeticObject {
    protected:
        virtual void __op(const Sum&) = 0;
        virtual void __op(const Multiplication&) = 0;
        virtual void __op(const Division&) = 0;
        virtual void __op(const Value&) = 0;
        virtual void __op(const Variable&) = 0;
        virtual void __op(const Logarithm&) = 0;

        template<Arithmetic T> void invokeOperation(const T&);
        void invokeOperation(const ArithmeticObject*);
    };
}

#endif //FUNCTIONS_OPERATOR_HH

#include "Operator.tcc"

