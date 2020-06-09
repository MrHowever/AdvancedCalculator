//
// Created by mrhowever on 16.02.2020.
//

#include "Variable.hh"
#include "IncludeValue.hh"

namespace MC::FN
{
    Variable::Variable(char val) : _value(val) {}

    void Variable::simplify()
    {

    }

    Value Variable::evaluate(const Value& val) const
    {
        return val;
    }

    ArithmeticType Variable::getType() const
    {
        return VAR;
    }

    std::string Variable::print() const
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

    bool Variable::operator<(const Variable& v) const
    {
        return _value < v._value;
    }
}


