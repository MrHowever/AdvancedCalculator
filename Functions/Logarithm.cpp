#include "Logarithm.hh"
#include "OperatorFactory.hh"

namespace MC::FN
{
    Logarithm::Logarithm() : _base(nullptr), _operand(nullptr)
    {

    }

    Logarithm::Logarithm(const Logarithm& l) : _base(OperatorFactory::copy(l._base)),
                                               _operand(OperatorFactory::copy(l._operand))
    {
    }

    Logarithm& Logarithm::operator=(const Logarithm& l)
    {
        _base = OperatorFactory::copy(l._base);
        _operand = OperatorFactory::copy(l._operand);
        return *this;
    };

    const ArithmeticObject* Logarithm::getBase() const
    {
        return _base;
    }

//    constexpr ArithmeticType Logarithm::getType() const
//    {
//        return LOG;
//    }

    Value Logarithm::evaluate(const Value& val) const
    {
        //TODO
        return val;
    }

    std::string Logarithm::print() const
    {
        return "log_(" + _base->print() + ")(" + _operand->print() + ")";
    }

    bool Logarithm::operator==(const Logarithm& log) const
    {
        return _base == log._base && _operand == log._operand;
    }

    bool Logarithm::operator!=(const Logarithm& o) const
    {
        return !(*this == o);
    }

    //TODO add constraint of same base
    Logarithm Logarithm::operator+(const Logarithm& log) const
    {
        Logarithm result = *this;
        result._operand = new Multiplication(result._operand,&log);
        return result;
    }

    Logarithm& Logarithm::operator+=(const Logarithm& log)
    {
        *this = *this + log;
        return *this;
    }
}
