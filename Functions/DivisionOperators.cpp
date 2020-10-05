#include "DivisionOperators.hh"
#include "MultiplicationOperators.hh"

namespace MC::FN
{
    ArithmeticPointerWrapper operator/(const Multiplication& o1, const Multiplication& o2)
    {
        if (compare(&o1, &o2))
            return new Value(1);

        auto commonCore = Multiplication::commonCore(o1, o2);

        if (commonCore != nullptr) {
            return o1.extract(commonCore) / o2.extract(commonCore);
        }

        return new Division(o1, o2);
    }

    DivisionPointerWrapper operator/(const Division& o1, const Division& o2)
    {
        return (o1.getNom() * o2.getDenom()) / (o1.getDenom() * o2.getNom());
    }

    DivisionPointerWrapper operator/(const Division& o1, const Multiplication& o2)
    {
        return o1.getNom() / (o1.getDenom() * o2);
    }

    DivisionPointerWrapper operator/(const Division& o1, const Value& o2)
    {
        if(o2 == Value(1)) {
            return new Division(o1);
        }

        return o1 * (1 / o2);
    }

    DivisionPointerWrapper operator/(const Exponentiation& o1, const Multiplication& o2)
    {
        auto isExpOrVar = [](auto& e) { return e->getType() == EXP || e->getType() == VAR; };
        auto sameBase = [&o1](auto& e) {
            return e->getType() == EXP ? compare(((ExponentiationPointerWrapper) e)->getBase(),o1.getBase()) : compare(e,o1.getBase());
        };

        auto candidates = o2 | std::views::filter(isExpOrVar);
        auto candidate = std::find_if(candidates.begin(), candidates.end(), sameBase);

        if(candidate != candidates.end()) {
            return ( o1 / *candidate) / o2.extract(*candidate);
        }

        return new Division(o1,o2);
    }

    ArithmeticPointerWrapper operator/(const Multiplication& o1, const Division& o2)
    {
        return (o1 * o2.getDenom()) / o2.getNom();
    }

    DivisionPointerWrapper operator/(const Multiplication& o1, const Exponentiation& o2)
    {
        auto result = o2 / o1;

        if(result->getType() == DIV) {
            DivisionPointerWrapper div = result;
            return new Division(div->getDenom(), div->getNom());
        } else {
            return 1 / result;
        }
    }

    ArithmeticPointerWrapper operator/(const Multiplication& o1, const Value& o2)
    {
        return (1 / o2) * o1;
    }

    DivisionPointerWrapper operator/(const Variable& o1, const Exponentiation& o2)
    {
        if(compare(&o1,o2.getBase())) {
            return 1 / (o2.getBase() ^ (o2.getPower() + (-1)));
        }

        return new Division(o1,o2);
    }

    DivisionPointerWrapper operator/(const Exponentiation& o1, const Variable& o2)
    {
        if (compare(o1.getBase(), &o2)) {
            return o1.getBase() ^ (o1.getPower() + (-1));
        }

        return new Division(o1, o2);

    }

    DivisionPointerWrapper operator/(const Exponentiation& o1, const Exponentiation& o2)
    {
        if (compare(o1.getBase(),o2.getBase())) {
            return o1.getBase() ^ (o1.getPower() + (-1 * o2.getPower()));
        }

        return new Division(o1, o2);

    }

    ArithmeticPointerWrapper operator/(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        switch(p2->getType())
        {
            case SUM: return p1 / p2.toRef<Sum>();
            case MUL: return p1 / p2.toRef<Multiplication>();
            case DIV: return p1 / p2.toRef<Division>();
            case VAR: return p1 / p2.toRef<Variable>();
            case VAL: return p1 / p2.toRef<Value>();
            case EXP: return p1 / p2.toRef<Exponentiation>();
            default: throw InvalidOperationException("Implementation error3");
        }
    }
}
