#include "Division.hh"
#include "Sum.hh"
#include <array>
#include "Variable.hh"

namespace MC::FN
{
    Division::Division(const Division& div) : Division()
    {
        _leftOp = div._leftOp.copyObject();
        _rightOp = div._rightOp.copyObject();
    }

    Division& Division::operator=(const Division& div)
    {
        _leftOp = div._leftOp.copyObject();
        _rightOp = div._rightOp.copyObject();
        return *this;
    }

    constexpr ArithmeticType Division::getType() const
    {
        return DIV;
    }

    Value Division::evaluate(const Value& val) const
    {
        return _leftOp->evaluate(val) / _rightOp->evaluate(val);
    }

    std::string Division::print()
    {
        std::string result;

        std::array<ArithmeticType, 3> nonbracedTypes = {VAL,
                                                        VAR,
                                                        LOG};

        if (std::find(nonbracedTypes.begin(), nonbracedTypes.end(), _leftOp->getType()) != nonbracedTypes.end())
            result += _leftOp->print();
        else {
            if(_leftOp->getType() == MUL) {
                MultiplicationPointerWrapper mult = _leftOp;

                if(std::all_of(mult->begin(), mult->end(), [](auto& e){
                    return e->getType() == VAR or e->getType() == VAL;
                })) {
                    result += _leftOp->print();
                } else {
                    result += addBraces(_leftOp->print());
                }
            } else {
                result += addBraces(_leftOp->print());
            }
        }

        result += " / ";

        if (std::find(nonbracedTypes.begin(), nonbracedTypes.end(), _rightOp->getType()) != nonbracedTypes.end())
            result += _rightOp->print();
        else {
            if(_rightOp->getType() == MUL) {
                MultiplicationPointerWrapper mult = _rightOp;

                if(std::all_of(mult->begin(), mult->end(), [](auto& e){
                    return e->getType() == VAR or e->getType() == VAL;
                })) {
                    result += _rightOp->print();
                } else {
                    result += addBraces(_rightOp->print());
                }
            } else {
                result += addBraces(_rightOp->print());
            }
        }
            

        return result;
    }

    const ArithmeticPointerWrapper& Division::getNom() const
    {
        return _leftOp;
    }

    const ArithmeticPointerWrapper& Division::getDenom() const
    {
        return _rightOp;
    }

    Division::~Division()
    {
        _leftOp.Delete();
        _rightOp.Delete();
    }

    Division::Division(const ArithmeticPointerWrapper& o1, const ArithmeticPointerWrapper& o2)
    {
        _leftOp = o1.copyObject();
        _rightOp = o2.copyObject();
    }
}