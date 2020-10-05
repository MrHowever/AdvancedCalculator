#include "Exponentiation.hh"
#include "Sum.hh"
#include "Division.hh"
#include "Variable.hh"

namespace MC::FN
{
    Exponentiation::Exponentiation(const Exponentiation& exp)
    {
        _leftOp = exp._leftOp.copyObject();
        _rightOp = exp._rightOp.copyObject();
    }

    Exponentiation& Exponentiation::operator=(const Exponentiation& exp)
    {
        _leftOp = exp._leftOp.copyObject();
        _rightOp = exp._rightOp.copyObject();
        return *this;
    }

    constexpr ArithmeticType Exponentiation::getType() const
    {
        return EXP;
    }
    
    Value Exponentiation::evaluate(const Value& val) const
    {
        return _leftOp->evaluate(val) ^ _rightOp->evaluate(val);
    }
    
    std::string Exponentiation::print()
    {
        std::string result;

        if(_leftOp->getType() == VAL or _leftOp->getType() == VAR or _leftOp->getType() == LOG)
            result += _leftOp->print();
        else
            result += "(" + _leftOp->print() + ")";

        result += " ^ ";

        if(_rightOp->getType() == VAL or _rightOp->getType() == VAR or _rightOp->getType() == LOG)
            result += _rightOp->print();
        else
            result += "(" + _rightOp->print() + ")";

        return result;
    }

    Exponentiation::~Exponentiation()
    {
        _leftOp.Delete();
        _rightOp.Delete();
    }

    const ArithmeticPointerWrapper& Exponentiation::getBase() const
    {
        return _leftOp;
    }

    const ArithmeticPointerWrapper& Exponentiation::getPower() const
    {
        return _rightOp;
    }

    Exponentiation::Exponentiation(const ArithmeticPointerWrapper& p1, const ArithmeticPointerWrapper& p2)
    {
        _leftOp = p1.copyObject();
        _rightOp = p2.copyObject();
    }
}