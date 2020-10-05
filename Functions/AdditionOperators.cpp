#include "AdditionOperators.hh"
#include "MultiplicationOperators.hh"
#include "DivisionOperators.hh"
#include "Sum.hh"

namespace MC::FN
{
    std::atomic<bool> swappedSum = false;

    ArithmeticPointerWrapper operator+(const Multiplication& o1, const Sum& o2)
    {
        return operator+<Sum>(o1,o2);
    }

    ArithmeticPointerWrapper operator+(const Sum& o1, const Multiplication& o2)
    {
        return operator+<Sum>(o2,o1);
    }

    ArithmeticPointerWrapper operator+(const Sum& o1, const Sum& o2)
    {
        auto result = SumPointerWrapper(&o1).copyObject();

        for (auto& elem : o2) {
            result->invokeOperation(elem);
        }

        return result;
    }

    ArithmeticPointerWrapper operator+(const Multiplication& o1, const Multiplication& o2)
    {
        auto common = Multiplication::commonCore(o1,o2);

        if(common != nullptr && common->getType() != VAL) {
            auto left  = o1.extract(common);
            auto right = o2.extract(common);
            return common * (left + right);
        }

        return new Sum(o1,o2);
    }

    [[nodiscard]] ArithmeticPointerWrapper operator+(const Multiplication& o1, const Division& o2)
    {
        return o2 + o1;
    }

    ArithmeticPointerWrapper operator+(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        switch(p2->getType())
        {
            case SUM: return p1 + p2.toRef<Sum>();
            case MUL: return p1 + p2.toRef<Multiplication>();
            case DIV: return p1 + p2.toRef<Division>();
            case VAR: return p1 + p2.toRef<Variable>();
            case VAL: return p1 + p2.toRef<Value>();
            case EXP: return p1 + p2.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error4");
        }
    }
}