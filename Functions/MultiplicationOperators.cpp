#include "MultiplicationOperators.hh"
#include "DivisionOperators.hh"
#include "AdditionOperators.hh"
#include "ExponentiationOperators.hh"

namespace MC::FN
{
    std::atomic<bool> swapped = false;

    ArithmeticPointerWrapper operator*(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        switch (p2->getType()) {
            case SUM: return p1 * p2.toRef<Sum>();
            case MUL: return p1 * p2.toRef<Multiplication>();
            case DIV: return p1 * p2.toRef<Division>();
            case VAR: return p1 * p2.toRef<Variable>();
            case VAL: return p1 * p2.toRef<Value>();
            case EXP: return p1 * p2.toRef<Exponentiation>();
            default:  throw InvalidOperationException("Implementation error1");
        }
    }

    ArithmeticPointerWrapper operator*(const Exponentiation& o1, const Division& o2)
    {
        if(compare(o1.getBase(), &o2)) {
            return o1.getBase() ^ (o1.getPower() + 1);
        }

        return (o1 * o2.getNom()) / o2.getDenom();
    }

    ArithmeticPointerWrapper operator*(const Exponentiation& o1, const Sum& o2)
    {
        if(compare(o1.getBase(),&o2)) {
            return o1.getBase() ^ (o1.getPower() + 1);
        }
        auto result = (SumPointerWrapper) new Sum();

        for(auto& elem : o2) {
            result->invokeOperation(o1 * elem);
        }

        return result;
    }

    ArithmeticPointerWrapper operator*(const Exponentiation& o1, const Multiplication& o2)
    {
        if(compare(o1.getBase(),&o2)) {
            return o1.getBase() ^ (o1.getPower() + 1);
        }

        for(auto& elem : o2) {
            auto mult = o1 * elem;

            if(mult->getType() != MUL) {
                auto result = o2.extract(elem);
                result = new Multiplication(result,mult);
                return result;
            }
        }

        return new Multiplication(o1,o2);
    }

    ArithmeticPointerWrapper operator*(const Multiplication& o1, const Multiplication& o2)
    {
        auto result = MultiplicationPointerWrapper(&o1).copyObject();

        for(auto& elem : o2) {
            result->invokeOperation(elem);
        }

        return result;
    }

    ArithmeticPointerWrapper operator*(const Multiplication& o1, const Sum& o2)
    {
        auto result = (SumPointerWrapper) new Sum();

        for(auto& elem : o2) {
            result->invokeOperation(elem * o1);
        }

        return result;
    }

    ArithmeticPointerWrapper operator*(const Multiplication& o1, const Division& o2)
    {
        return operator*<Multiplication>(o2,o1);
    }

    ArithmeticPointerWrapper operator*(const Sum& o1, const Multiplication& o2)
    {
        auto result = (SumPointerWrapper) new Sum();

        for(auto& elem : o1) {
            result->invokeOperation(elem * o2);
        }

        return result;
    }

    ArithmeticPointerWrapper operator*(const Sum& o1, const Sum& o2)
    {
        auto result = (SumPointerWrapper) new Sum();

        for(auto& e1 : o1) {
            for (auto& e2 : o2) {
                result->invokeOperation(e1 * e2);
            }
        }

        return result;
    }

    ArithmeticPointerWrapper operator*(const Sum& o1, const Value& o2)
    {
        return o2 * o1;
    }

    ArithmeticPointerWrapper operator*(const Value& o1, const Multiplication& o2)
    {
        if(o1 == Value(0)) {
            return new Value(0);
        }

        if(o1 == Value(1)) {
            return new Multiplication(o2);
        }

        auto val = std::find_if(o2.begin(), o2.end(), [](auto& e) {
            return e->getType() == VAL;
        });

        if(val != o2.end()) {
            Value newVal = o1 * (*val).toRef<Value>();
            auto result = o2.extract(*val);
            result = result * newVal;
            return result;
        }

        return new Multiplication(o1,o2);
    }

    ArithmeticPointerWrapper operator*(const Value& o1, const Sum& o2)
    {
        if(o1 == Value(0)) {
            return new Value(0);
        }

        if(o1 == Value(1)) {
            return SumPointerWrapper(&o2).copyObject();
        }

        auto sum = (SumPointerWrapper) new Sum();

        for(auto& elem : o2) {
            sum = sum + (elem * o1);
        }

        return sum;
    }

    ArithmeticPointerWrapper operator*(const Multiplication& o1, const Value& o2)
    {
        return o2 * o1;
    }

    ArithmeticPointerWrapper operator*(const Division& o1, const Multiplication& o2)
    {
        return operator*<Multiplication>(o1,o2);
    }
}

