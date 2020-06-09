//
// Created by mrhowever on 15.02.2020.
//

#ifndef FUNCTIONS_SUM_TCC
#define FUNCTIONS_SUM_TCC

#include "Multiplication.hh"
#include "IncludeDivision.hh"
#include "Variable.hh"
#include "InvalidOperationException.hh"
#include "Logarithm.hh"
#include "IncludeLogarithmMap.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Sum::Sum(const T& o1, const P& o2) : Sum()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<typename T, typename P, typename>
    [[nodiscard]] Sum operator+(const T& o1, const P& o2)
    {
        return Sum(o1,o2);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Sum operator+(const T& first, const P& second)
    {
        return first + Value(second);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Sum operator+(const P& first, const T& second)
    {
        return second + Value(first);
    }

    //TODO  handle built-in arithmetic types
    template<typename T>
    void Sum::__add(const T&)
    {
        throw InvalidOperationException("Unhandled ArithmeticObject type ");
    }


    template<typename T, typename>
    void Sum::invokeOperation(const T& o)
    {
        __add<T>(o);
    }

    template<typename T, typename>
    void Sum::invokeOperation(const T* o)
    {
        switch(o->getType())
        {
            case SUM: invokeOperation(*dynamic_cast<const Sum*>(o));            break;
            case MUL: invokeOperation(*dynamic_cast<const Multiplication*>(o)); break;
            case DIV: invokeOperation(*dynamic_cast<const Division*>(o));       break;
            case LOG: invokeOperation(*dynamic_cast<const Logarithm*>(o));      break;
            case VAR: invokeOperation(*dynamic_cast<const Variable*>(o));       break;
            case VAL: invokeOperation(*dynamic_cast<const Value*>(o));          break;
        }
    }

}
#endif //FUNCTIONS_SUM_TCC
