//
// Created by mrhowever on 15.02.2020.
//

#ifndef FUNCTIONS_DIVISION_TCC
#define FUNCTIONS_DIVISION_TCC

#include "Multiplication.hh"
#include "Logarithm.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Division::Division(const T& o1, const P& o2) : Division()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<typename T, typename P, typename>
    [[nodiscard]] Division operator/(const T& o1, const P& o2)
    {
        return Division(o1,o2);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Division operator/(const T& first, const P& second)
    {
        return first / Value(second);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Division operator/(const P& first, const T& second)
    {
        return Value(first) / second;
    }

    template<typename T>
    void Division::_div(const T& o)
    {
        if(!_nom)
            _nom = new T(o);
        else {
            _denom = _denom ? (ArithmeticObject *) new Multiplication(_denom, &o) : (ArithmeticObject *) new T(o);
            simplify();
        }
    }

    template<typename T, typename>
    void Division::invokeOperation(const T& o)
    {
        _div(o);
    }

    template<typename T, typename>
    void Division::invokeOperation(const T* o)
    {
        switch(o->getType())
        {
            case SUM: invokeOperation(dynamic_cast<const Sum&>(*o));            break;
            case MUL: invokeOperation(dynamic_cast<const Multiplication&>(*o)); break;
            case DIV: invokeOperation(dynamic_cast<const Division&>(*o));       break;
            case LOG: invokeOperation(dynamic_cast<const Logarithm&>(*o));      break;
            case VAR: invokeOperation(dynamic_cast<const Variable&>(*o));       break;
            case VAL: invokeOperation(dynamic_cast<const Value&>(*o));          break;
        }
    }
}

#endif //FUNCTIONS_DIVISION_TCC
