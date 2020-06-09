//
// Created by mrhowever on 24.03.2020.
//

#include "OperatorFactory.hh"
#include "IncludeSum.hh"

namespace MC::FN
{
    template<typename T>
    ArithmeticObject* OperatorFactory::copy(const T* oPtr)
    {
        switch(oPtr->getType())
        {
            case SUM: return new Sum(*dynamic_cast<const Sum*>(oPtr));
            case MUL: return new Multiplication(*dynamic_cast<const Multiplication*>(oPtr));
            case DIV: return new Division(*dynamic_cast<const Division*>(oPtr));
            case LOG: return new Logarithm(*dynamic_cast<const Logarithm*>(oPtr));
            case VAR: return new Variable(*dynamic_cast<const Variable*>(oPtr));
            case VAL: return new Value(*dynamic_cast<const Value*>(oPtr));
        }
    }
}