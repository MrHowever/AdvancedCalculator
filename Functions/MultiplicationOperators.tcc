#ifndef FUNCTIONS_MULTIPLICATIONOPERATORS_TCC
#define FUNCTIONS_MULTIPLICATIONOPERATORS_TCC

#include "ArithmeticPointerWrapper.hh"
#include "ExponentiationOperators.hh"
#include <algorithm>
#include "Exponentiation.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Variable.hh"
#include "Value.hh"
#include "DivisionOperators.hh"
#include <atomic>

namespace MC::FN
{
    template<ArithmeticRef T>
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Division& o1, const T& o2)
    {
        return (o1.getNom() * o2) / o1.getDenom();
    }

    template<ArithmeticRef T>
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Sum& o1, const T& o2)
    {
        auto result = (SumPointerWrapper) new Sum();

        for(auto& elem : o1) {
            result->invokeOperation(elem * o2);
        }

        return result;
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator*(const Exponentiation& o1, const T& o2)
    {
        if constexpr (std::is_same_v<Exponentiation,T>) {
            if(compare(o1.getBase(), o2.getBase())) {
                return (ExponentiationPointerWrapper) new Exponentiation(o1.getBase(), o1.getPower() + o2.getPower());
            }
        }

        if (compare(o1.getBase(), (PointerWrapper<T>) &o2)) {
            return o1.getBase() ^ (o1.getPower() + Value(1));
        } else {
            return (MultiplicationPointerWrapper) new Multiplication(o1, o2);
        }
    }

    //TODO this is gonna be terrible for multithreading
    extern std::atomic<bool> swapped;

    template<ArithmeticRef T, ArithmeticRef P>
    [[nodiscard]] ArithmeticPointerWrapper operator*(const T& o1, const P& o2)
    {
        if(!swapped) {
            swapped = true;
            auto result = o2 * o1;
            swapped = false;
            return result;
        }

        if(compare((PointerWrapper<T>) &o1,(PointerWrapper<P>) &o2))
            return (ExponentiationPointerWrapper) new Exponentiation(o1, Value(2));

        return (MultiplicationPointerWrapper) new Multiplication(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator*(const Value& o1, const T& o2)
    {
        if(o1 == Value(0)) {
            return ValuePointerWrapper(new Value(0));
        }

        if(o1 == Value(1)) {
            return PointerWrapper<T>(new T(o2));
        }

        return (MultiplicationPointerWrapper) new Multiplication(o1,o2);
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator*(const Multiplication& o1, const T& o2)
    {
        auto result = PointerWrapper<Multiplication>(&o1).copyObject();
        result->invokeOperation(o2);
        return result;
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator*(const T& o, const ArithmeticPointerWrapper& p)
    {
        switch(p->getType())
        {
            case SUM: return o * p.toRef<Sum>();
            case MUL: return o * p.toRef<Multiplication>();
            case DIV: return o * p.toRef<Division>();
            case VAR: return o * p.toRef<Variable>();
            case VAL: {
                if constexpr(std::is_same_v<decltype(o * p.toRef<Value>()), Value>)
                    return ValuePointerWrapper(new Value(o * p.toRef<Value>()));
                else
                    return o * p.toRef<Value>();
            }

            case EXP: return o * p.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error1");
        }
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator*(const ArithmeticPointerWrapper& p, const T& o)
    {
        switch(p->getType())
        {
            case SUM: return p.toRef<Sum>() * o;
            case MUL: return p.toRef<Multiplication>() * o;
            case DIV: return p.toRef<Division>() * o;
            case VAR: return p.toRef<Variable>() * o;
            case VAL:  {
                if constexpr(std::is_same_v<decltype(p.toRef<Value>() * o), Value>)
                    return ValuePointerWrapper(new Value((p.toRef<Value>() * o)));
                else
                    return p.toRef<Value>() * o;
            }

            case EXP: return p.toRef<Exponentiation>() * o;

            default: throw InvalidOperationException("Implementation error1");
        }
    }
}

#endif //FUNCTIONS_MULTIPLICATIONOPERATORS_TCC
