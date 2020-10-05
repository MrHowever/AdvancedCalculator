#include "Variable.hh"
#include "ArithmeticPointerWrapper.hh"
#include "Sum.hh"
#include "Exponentiation.hh"
#include "Division.hh"

namespace MC::FN
{
    Variable::Variable(char sign) : _value(sign) {}

    Value Variable::evaluate(const Value& val) const
    {
        return val;
    }

    constexpr ArithmeticType Variable::getType() const
    {
        return VAR;
    }

    std::string Variable::print()
    {
        return std::string(1, _value);
    }

    bool Variable::operator==(const Variable& var) const
    {
        return _value == var._value;
    }

    bool Variable::operator!=(const Variable& o2) const
    {
        return !(*this == o2);
    }

    char Variable::getValue() const
    {
        return _value;
    }
}


