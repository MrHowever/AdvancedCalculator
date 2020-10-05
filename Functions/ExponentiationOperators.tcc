#ifndef FUNCTIONS_EXPONENTIATIONOPERATORS_TCC
#define FUNCTIONS_EXPONENTIATIONOPERATORS_TCC

#include "ArithmeticPointerWrapper.hh"
#include "Exponentiation.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Variable.hh"
#include "Value.hh"

namespace MC::FN
{
    template<ArithmeticRef T, ArithmeticRef P>
    [[nodiscard]] ArithmeticPointerWrapper operator^(const T& o1, const P& o2)
    {
        return new Exponentiation(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator^(const Exponentiation& o1, const T& o2)
    {
        return o1.getBase() ^ (o1.getPower() * o2);
    }


    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator^(const Value& o1, const T& o2)
    {
        if(o1 == Value(0)) {
            return new Value(0);
        }

        if(o1 == Value(1)) {
            return new Value(1);
        }

        return new Exponentiation(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator^(const T& o1, const Value& o2)
    {
        if(o2 == Value(0)) {
            return new Value(1);
        }

        if(o2 == Value(1)) {
            return new T(o1);
        }

        if(o2 < Value(0)) {
            return 1 / (o1 ^ (o2 * (-1)));
        }

        return new Exponentiation(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator^(const T& o, const ArithmeticPointerWrapper& p)
    {
        switch(p->getType())
        {
            case SUM: return o ^ p.toRef<Sum>();
            case MUL: return o ^ p.toRef<Multiplication>();
            case DIV: return o ^ p.toRef<Division>();
            case VAR: return o ^ p.toRef<Variable>();

            case VAL:  {
                if constexpr(std::is_same_v<decltype(o ^ p.toRef<Value>()), Value>)
                    return ValuePointerWrapper(new Value(o ^ p.toRef<Value>()));
                else
                    return o ^ p.toRef<Value>();
            }

            case EXP: return o ^ p.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error2");
        }
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator^(const ArithmeticPointerWrapper& p, const T& o)
    {
        switch(p->getType())
        {
            case SUM: return p.toRef<Sum>() ^ o;
            case MUL: return p.toRef<Multiplication>() ^ o;
            case DIV: return p.toRef<Division>() ^ o;
            case VAR: return p.toRef<Variable>() ^ o;

            //TODO can this be reduced to a func? its called in every func
            case VAL:  {
                if constexpr(std::is_same_v<decltype(p.toRef<Value>() ^ o), Value>)
                    return ValuePointerWrapper(new Value((p.toRef<Value>() ^ o)));
                else {
                    return operator^<T>(p.toRef<Value>(),o);
                }
            }

            case EXP: return p.toRef<Exponentiation>() ^ o;
            default: throw InvalidOperationException("Implementation error2");
        }
    }

}

#endif //FUNCTIONS_EXPONENTIATIONOPERATORS_TCC
