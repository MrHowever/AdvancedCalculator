#include "Division.hh"
#include "Multiplication.hh"
#include "Sum.hh"
#include "Variable.hh"
#include "SortHash.hh"

namespace MC::FN
{
    Multiplication::Multiplication(const ArithmeticPointerWrapper & o1, const ArithmeticPointerWrapper & o2) : Multiplication()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    Multiplication::Multiplication(const Multiplication& mult) : Multiplication()
    {
        copy(mult);
    }

    Multiplication& Multiplication::operator=(const Multiplication& mult)
    {
        clear();
        copy(mult);
        return *this;
    }

    constexpr ArithmeticType Multiplication::getType() const
    {
        return MUL;
    }

    Value Multiplication::evaluate(const Value& value) const
    {
        Value result(1);
        for_each([&value,&result](auto& e) { result *= e->evaluate(value); });
        return result;
    }

    std::string Multiplication::print()
    {
        std::string result;

        _operands.sort([](auto& e1, auto& e2) {
            return SortHash<Multiplication>::sortHash(e1) < SortHash<Multiplication>::sortHash(e2);
        });

        for (auto& elem : _operands) {
            if (elem->getType() == SUM || elem->getType() == EXP) {
                result += addBraces(elem->print());
            } else {
                if(elem->getType() == VAL && elem.toRef<Value>() == Value(-1))
                    result += "-";
                else
                    result += elem->print();
            }
        }

        return result;
    }

    ArithmeticPointerWrapper Multiplication::extract(const ArithmeticPointerWrapper& o) const
    {
        auto result = MultiplicationPointerWrapper(this).copyObject();

        if (o->getType() == MUL) {
            return _extractMult(o);
        }

        if (o->getType() == VAL) {
            return _extractVal(o);
        }

        if (o->getType() == EXP) {
            return _extractExp(o);
        }

        if (o->getType() == VAR) {
            return _extractVar(o);
        }

        result->remove(o);

        if (result->size() == 0)
            return (ValuePointerWrapper) new Value(1);

        if (result->size() == 1)
            return result->begin()->copyObject();

        return result;
    }

    Multiplication::~Multiplication()
    {
        clear();
    }

    void Multiplication::invokeOperation(const ArithmeticPointerWrapper& o)
    {
        switch(o->getType())
        {
            case SUM: invokeOperation(*dynamic_cast<const Sum*>(o.get()));            break;
            case MUL: invokeOperation(*dynamic_cast<const Multiplication*>(o.get())); break;
            case DIV: invokeOperation(*dynamic_cast<const Division*>(o.get()));       break;
            case VAR: invokeOperation(*dynamic_cast<const Variable*>(o.get()));       break;
            case VAL: invokeOperation(*dynamic_cast<const Value*>(o.get()));         break;
            case EXP: invokeOperation(*dynamic_cast<const Exponentiation*>(o.get())); break;
        }
    }

    ArithmeticPointerWrapper Multiplication::_extractMult(const MultiplicationPointerWrapper& o) const
    {
        auto result = MultiplicationPointerWrapper(this).copyObject();

        for(auto& elem : *o) {
            if(result->getType() != MUL && compare(result,elem))
                return new Value(1);

            result = result->extract(elem);
        }

        return result;
    }

    ArithmeticPointerWrapper Multiplication::_extractVal(const ValuePointerWrapper& o) const
    {
        auto result = MultiplicationPointerWrapper(this).copyObject();

        auto valuePtr = std::find_if(result->begin(), result->end(), [](auto& e) { return e->getType() == VAL; } );
        Value newVal = (*valuePtr / o).toRef<Value>();

        result->remove(*valuePtr);
        result = result * newVal;

        if(result->size() == 1)
            return result->begin()->copyObject();

        return result;
    }

    ArithmeticPointerWrapper Multiplication::_extractVar(const VariablePointerWrapper & o) const
    {
        auto result = MultiplicationPointerWrapper(this).copyObject();

        if(result->contains(o)) {
            auto exp = std::find_if(result->begin(), result->end(), [&o](auto& e){
                return e->getType() == EXP && compare(((ExponentiationPointerWrapper)e)->getBase(),o);
            });

            if(exp != result->end()) {
                ExponentiationPointerWrapper oldExp = *exp;
                ExponentiationPointerWrapper newExp = oldExp->getBase() ^ (oldExp->getPower() + -1);

                result->remove(oldExp);
                result->add(newExp);

                return result;
            }

            result->remove(o);

            if(result->size() == 1)
                return result->begin()->copyObject();

            return result;
        }

        return result;
    }

    ArithmeticPointerWrapper Multiplication::_extractExp(const ExponentiationPointerWrapper& o) const
    {
        auto result = MultiplicationPointerWrapper(this).copyObject();

        if(result->contains(o)) {

            auto isExp = [](auto& e) { return e->getType() == EXP; };
            auto sameBase = [](const ExponentiationPointerWrapper& e1, const ExponentiationPointerWrapper& e2) {
                return compare(e1->getBase(), e2->getBase());
            };

            ExponentiationPointerWrapper exp = *std::find_if(result->begin(), result->end(), [&isExp,&sameBase,&o](auto& e) {
                return isExp(e) && sameBase(e,o);
            });
            
            
            auto newExp = exp / o;
            result->remove(exp);
            ArithmeticPointerWrapper genericResult = result * newExp;

            if(genericResult->getType() == MUL && (genericResult.cast<Multiplication>())->size() == 1)
                return genericResult.cast<Multiplication>()->begin()->copyObject();

            return genericResult;
        }

        auto isExp = [](auto& e) { return e->getType() == EXP; };
        auto sameBase = [](const ExponentiationPointerWrapper& e1, const ExponentiationPointerWrapper& e2) {
            return compare(e1->getBase(), e2->getBase());
        };

        ExponentiationPointerWrapper exp = *std::find_if(result->begin(), result->end(), [&isExp,&sameBase,&o](auto& e) {
            return isExp(e) && sameBase(e,o);
        });

        auto newExp = o->getBase() ^ (exp->getPower() + ((-1) * o->getPower()));
        result->remove(exp);
        result->add(newExp);
        return result;
    }
}
