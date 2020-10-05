#ifndef FUNCTIONS_DIVISIONOPERATORS_TCC
#define FUNCTIONS_DIVISIONOPERATORS_TCC

#include "ArithmeticPointerWrapper.hh"
#include "Exponentiation.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Variable.hh"
#include "Value.hh"

namespace MC::FN
{
    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const T& o1, const Multiplication& o2)
    {
        if(o2.contains(&o1))
            return 1 / o2.extract(&o1);
        else
            return new Division(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const Division& o1, const T& o2)
    {
        return o1.getNom() / (o1.getDenom() * o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const T& o1, const Division& o2)
    {
        return (o1 * o2.getDenom()) / o2.getNom();
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const T& o1, const Value& o2)
    {
        return (1 / o2) * o1;
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const Multiplication& o1, const T& o2)
    {
        if (o1.contains(&o2)) {
            return o1.extract(&o2);
        }

        return new Division(o1, o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const T& o, const ArithmeticPointerWrapper& p)
    {
        switch(p->getType())
        {
            case SUM: return o / p.toRef<Sum>();
            case MUL: return o / p.toRef<Multiplication>();
            case DIV: return o / p.toRef<Division>();
            case VAR: return o / p.toRef<Variable>();

            case VAL:  {
                if constexpr(std::is_same_v<decltype(o / p.toRef<Value>()), Value>)
                    return ValuePointerWrapper(new Value(o / p.toRef<Value>()));
                else
                    return o / p.toRef<Value>();
            }

            case EXP: return o / p.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error3");
        }
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator/(const ArithmeticPointerWrapper& p, const T& o)
    {
        switch(p->getType())
        {
            case SUM: return p.toRef<Sum>() / o;
            case MUL: return p.toRef<Multiplication>() / o;
            case DIV:  return p.toRef<Division>() / o;
            case VAR: return p.toRef<Variable>() / o;

            case VAL:  {
                if constexpr(std::is_same_v<decltype(p.toRef<Value>() / o), Value>)
                    return ValuePointerWrapper(new Value((p.toRef<Value>() / o)));
                else
                    return p.toRef<Value>() / o;
            }

            case EXP: return p.toRef<Exponentiation>() / o;
            default: throw InvalidOperationException("Implementation error3");
        }
    }

    template<ArithmeticRef T, ArithmeticRef P>
    [[nodiscard]] ArithmeticPointerWrapper operator/(const T& o1, const P& o2)
    {
        if(compare(&o1, &o2))
            return new Value(1);

        return new Division(o1,o2);
    }
}

#endif //FUNCTIONS_DIVISIONOPERATORS_TCC
