#include <algorithm>
#include "Sum.hh"
#include "Division.hh"
#include "Variable.hh"
#include "SortHash.hh"

namespace MC::FN
{
    Sum::Sum(const Sum& sum) : Sum()
    {
        copy(sum);
    }

    Sum& Sum::operator=(const Sum& o)
    {
        clear();
        copy(o);
        return *this;
    }

    //TODO for more than 1 variable it needs to take list of values
    Value Sum::evaluate(const Value& val) const
    {
        Value result(1);
        for_each([&val,&result](auto& e) { result += e->evaluate(val); });
        return result;
    }

    std::string Sum::print()
    {
        std::string result;

        _operands.sort([](auto& e1, auto& e2) {
            return SortHash<Sum>::sortHash(e1) < SortHash<Sum>::sortHash(e2);
        });

        for(auto& elem : _operands) {
            result += elem->print() + " + ";
        }

        // Remove the unnecessary plus sign at the end of the line
        return result.erase(result.size() - 3, 3);
    }

    // Return type identifier for polymorphic type recognition
    constexpr ArithmeticType Sum::getType() const
    {
        return SUM;
    }

    Sum::~Sum()
    {
        clear();
    }

    void Sum::invokeOperation(const ArithmeticPointerWrapper& o)
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

    Sum::Sum(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        invokeOperation(p1);
        invokeOperation(p2);
    }
}
