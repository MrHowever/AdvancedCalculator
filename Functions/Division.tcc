#ifndef FUNCTIONS_DIVISION_TCC
#define FUNCTIONS_DIVISION_TCC

#include "Operator.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Division::Division(const T& o1, const P& o2) : Division()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Division operator/(const T& o1, const P& o2)
    {
        return Division(o1,o2);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Division operator/(const T& first, const P& second)
    {
        return first / Value(second);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Division operator/(const P& first, const T& second)
    {
        return Value(first) / second;
    }

    template<typename T>
    void Division::__genOp(const T& o)
    {
        if(!_nom)
            _nom = new T(o);
        else {
            _denom = _denom ? (ArithmeticObject *) new Multiplication(_denom, &o) : (ArithmeticObject *) new T(o);
            simplify();
        }
    }
}

#endif //FUNCTIONS_DIVISION_TCC
