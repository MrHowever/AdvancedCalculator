#include "Variable.hh"

namespace MC::FN
{
    Variable::Variable(char val) : _value(val), _factor(1) {}

    Value Variable::evaluate(const Value& val) const
    {
        return val * _factor;
    }

    constexpr ArithmeticType Variable::getType() const
    {
        return VAR;
    }

    std::string Variable::print() const
    {
        return (_factor != Value(1) ? _factor.print() : "") + _value;
    }

    bool Variable::operator==(const Variable& var) const
    {
        return _value == var._value and _factor == var._factor;
    }

    bool Variable::operator!=(const Variable& o2) const
    {
        return !(*this == o2);
    }

    bool Variable::operator<(const Variable& v) const
    {
        return _value < v._value;
    }

    char Variable::getSign() const
    {
        return _value;
    }

    Variable::Variable(const Value& val, char sign) : _value(sign), _factor(val)
    {

    }

    Value Variable::getFactor() const
    {
        return _factor;
    }
}


