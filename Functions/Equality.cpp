#include "ArithmeticObject.hh"
#include "Equality.hh"

namespace MC::FN
{
//    constexpr ArithmeticType Equality::getType() const
//    {
//        return EQ;
//    }

    //TODO implicit int->Value, bool->Value
    Value Equality::evaluate(const Value& val) const
    {
        if(_first->getType() != _second->getType())
            return Value(0);

        switch(_first->getType())
        {
            case SUM: return Value(dynamic_cast<const Sum&>(*_first).operator==(dynamic_cast<const Sum&>(*_second)));
            case MUL: return Value(dynamic_cast<const Multiplication&>(*_first).operator==(dynamic_cast<const Multiplication&>(*_second)));
            case DIV: return Value(dynamic_cast<const Division&>(*_first).operator==(dynamic_cast<const Division&>(*_second)));
            case LOG: return Value(dynamic_cast<const Logarithm&>(*_first).operator==(dynamic_cast<const Logarithm&>(*_second)));
            case VAR: return Value(dynamic_cast<const Variable&>(*_first).operator==(dynamic_cast<const Variable&>(*_second)));
            case VAL: return Value(dynamic_cast<const Value&>(*_first).operator==(dynamic_cast<const Value&>(*_second)));
        }

        return Value(0);
    }

    std::string Equality::print() const
    {
        return _first->print() + " == "  + _second->print();
    }

    void Equality::__op(const Division& o)
    {
        __genOp(o);
    }

    void Equality::__op(const Sum& o)
    {
        __genOp(o);
    }

    void Equality::__op(const Multiplication& o)
    {
        __genOp(o);
    }

    void Equality::__op(const Value& o)
    {
        __genOp(o);
    }

    void Equality::__op(const Variable& o)
    {
        __genOp(o);
    }

    void Equality::__op(const Logarithm& o)
    {
        __genOp(o);
    }
}