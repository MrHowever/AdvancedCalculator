#include "ExponentiationOperators.hh"
#include "MultiplicationOperators.hh"

namespace MC::FN
{

    ArithmeticPointerWrapper operator^(const Exponentiation& o1, const Value& o2)
    {
        if(o2 == Value(0)) {
            return new Value(1);
        }

        if(o2 == Value(1)) {
            return new Exponentiation(o1);
        }

        return o1.getBase() ^ (o1.getPower() * o2);
    }

    ArithmeticPointerWrapper operator^(const Value& o1, const Exponentiation& o2)
    {
        if(o1 == Value(0)) {
            return new Value(0);
        }

        if(o1 == Value(1)) {
            return new Value(1);
        }

        return new Exponentiation(o1,o2);
    }
    
    ArithmeticPointerWrapper operator^(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        switch(p2->getType())
        {
            case SUM: return p1 ^ p2.toRef<Sum>();
            case MUL: return p1 ^ p2.toRef<Multiplication>();
            case DIV: return p1 ^ p2.toRef<Division>();
            case VAR: return p1 ^ p2.toRef<Variable>();
            case VAL: return p1 ^ p2.toRef<Value>();
            case EXP: return p1 ^ p2.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error2");
        }
    }
}