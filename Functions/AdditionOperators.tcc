#ifndef FUNCTIONS_ADDITIONOPERATORS_TCC
#define FUNCTIONS_ADDITIONOPERATORS_TCC

#include "ArithmeticPointerWrapper.hh"
#include "Exponentiation.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Variable.hh"
#include "Value.hh"
#include "MultiplicationOperators.hh"
#include <atomic>

namespace MC::FN
{
    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator+(const Multiplication& o1, const T& o2)
    {
        if (o1.contains(&o2)) {
            auto mult = o1.extract(&o2);
            return o2 * (mult + 1);
        } else {
            return new Sum(o1, o2);
        }
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator+(const Sum& o1, const T& o2)
    {
        auto result = PointerWrapper<T>(&o2).copyObject();

        for(auto& elem : o1) {
            if (result->getType() == SUM)
                result = SumPointerWrapper(new Sum(result,elem));
            else {
                result = result + elem;
            }
        }

        return result;
    }

    template<ArithmeticRef T>
    DivisionPointerWrapper operator+(const Division& o1, const T& o2)
    {
        if constexpr(std::is_same_v<T,Division>) {
            return (((o1.getNom() * o2.getDenom()) + (o2.getNom() * o1.getDenom())) /
                    (o1.getDenom() * o2.getDenom()));
        }

        return ((o2 * o1.getDenom()) + o1.getNom()) / o1.getDenom();
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator+(const T& o, const ArithmeticPointerWrapper& p)
    {
        switch(p->getType())
        {
            case SUM: return o + p.toRef<Sum>();
            case MUL: return o + p.toRef<Multiplication>();
            case DIV: return o + p.toRef<Division>();
            case VAR: return o + p.toRef<Variable>();

            case VAL:  {
                if constexpr(std::is_same_v<decltype(o + p.toRef<Value>()), Value>)
                    return ValuePointerWrapper(new Value(o + p.toRef<Value>()));
                else
                    return o + p.toRef<Value>();
            }

            case EXP: return o + p.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error4");
        }
    }

    template<ArithmeticRef T>
    ArithmeticPointerWrapper operator+(const ArithmeticPointerWrapper& p, const T& o)
    {
        switch(p->getType())
        {
            case SUM: return p.toRef<Sum>() + o;
            case MUL: return p.toRef<Multiplication>() + o;
            case DIV: return p.toRef<Division>() + o;
            case VAR: return p.toRef<Variable>() + o;

            case VAL:  {
                if constexpr(std::is_same_v<decltype(p.toRef<Value>() + o), Value>)
                    return ValuePointerWrapper(new Value((p.toRef<Value>() + o)));
                else
                    return p.toRef<Value>() + o;
            }

            case EXP: return p.toRef<Exponentiation>() + o;
            default: throw InvalidOperationException("Implementation error4");
        }
    }

    //TODO this is gonna be terrible for multithreading
    extern std::atomic<bool> swappedSum;

    template<ArithmeticRef T, ArithmeticRef P>
    ArithmeticPointerWrapper operator+(const T& o1, const P& o2)
    {
        if(!swappedSum) {
            swappedSum = true;
            auto result = o2 + o1;
            swappedSum = false;
            return result;
        }

        if(compare(&o1,&o2))
            return new Multiplication(Value(2), o1);

        return new Sum(o1,o2);
    }
}

#endif //FUNCTIONS_ADDITIONOPERATORS_TCC
