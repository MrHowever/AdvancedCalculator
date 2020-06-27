#include "Sum.hh"
#include "Logarithm.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "OperatorFactory.hh"

#include <algorithm>

namespace MC::FN
{
    Sum::Sum() : _value(nullptr), _div(nullptr)
    {
    }

    Sum::Sum(const Sum& sum) : Sum()
    {
        for(ArithmeticObject* elem : sum._faList) {
            invokeOperation(elem);
        }
    }

    // Return type identifier for polymorphic type recognition
    constexpr ArithmeticType Sum::getType() const
    {
        return SUM;
    }

    //TODO for more than 1 variable it needs to take list of values
    Value Sum::evaluate(const Value& val) const
    {
        Value result(0);

        std::for_each(_logs.begin(), _logs.end(), [&result,&val](auto& elem) {
            result += elem.second->evaluate(val);
        });

        std::for_each(_muls.begin(), _muls.end(), [&result,&val](auto& elem) {
            result += elem->evaluate(val);
        });

        std::for_each(_vars.begin(), _vars.end(), [&result,&val](auto& elem) {
            result += elem.second->getFactor();
        });

        result += _div->evaluate(val);
        result += *_value;

        return result;
    }

    bool Sum::operator==(const Sum& sum) const
    {
        // Compare logarithms
        if(_logs.size() != sum._logs.size())
            return false;

        for(auto& elem : _logs) {
            if(!sum._logs.contains(elem.first))
                return false;

            if(sum._logs.at(elem.first) != elem.second)
                return false;
        }

        // Compare multiplications
        if(_muls.size() != sum._muls.size())
            return false;

        for(auto& elem : _muls) {
            bool found = false;

            for(auto& second : sum._muls) {
                if(*second == *elem) {
                    found = true;
                    break;
                }

                return false;
            }

            if(!found)
                return false;
        }

        // Compare variables
        if(_vars.size() != sum._vars.size())
            return false;

        for(auto& elem : _vars) {
            if(!sum._vars.contains(elem.first))
                return false;

            if(sum._vars.at(elem.first) != elem.second)
                return false;
        }

        // Compare divisions and value
        return *_div == *sum._div && *_value == *sum._value;
    }

    bool Sum::operator!=(const Sum& o) const
    {
        return !(*this == o);
    }

    // Return iterator to "first" element in sum
    SumIterator Sum::begin() const
    {
        return SumIterator(*this);
    }

    // Return iterator to element after the "last" sum element
    SumIterator Sum::end() const
    {
        return SumIterator::end(*this);
    }

    // Return sum of two divisions which is a division as well
    Division operator+(const Division& first, const Division& second)
    {
        return (Multiplication(first.getNom(),second.getDenom()) + Multiplication(second.getNom(),first.getDenom())) /
                        Multiplication(first.getDenom(),second.getDenom());
    }

    // Add division to current sum
    void Sum::__op(const Division& o)
    {
        if(_div) {
            // If division already exists, replace it with sum of old and new division
            *_div = *_div + o;
        }
        else {
            // If division doesn't exist add it to fast access list and save Division pointer to it's place in the list
            _div = new Division(o);
            _faList.push_back(_div);
        }
    }

    // Add another sum to current sum
    void Sum::__op(const Sum& o)
    {
        for (auto& elem : o._faList) {
            invokeOperation(elem);
        }
    }

    //TODO value * division = division

    void Sum::__op(const Multiplication& o)
    {
        std::string xd = o.print();

        const Multiplication::Base& base = o._base;

        if(base.is<Variable>()) {
            Variable var = o._value * base._vars.begin()->first;

            if(_vars.contains(o._base._vars.begin()->first.getSign())) {
                *_vars[var.getSign()] =  Variable(_vars[var.getSign()]->getFactor() + var.getFactor(), var.getSign());
            }
            else {
                _vars[var.getSign()] =  new Variable(var);
                _faList.push_back(_vars[var.getSign()]);
            }
        }
        else if(base.is<Sum>()) {
            for(int i = 0; o._value > i; i++) {
                __op(*o._base._sum);
            }
        }
        else if(base.is<Logarithm>()) {
            Logarithm tempLog = o._base._logs.begin()->second.front();
            //TODO 2*log(x) -> log(2x) -> __op(log2x)
        }
        else {
            for (Multiplication* mult : _muls) {
                if(mult) {
                    if (mult->_base == o._base) {
                        // Retarded way of avoiding new functions to add value to multiplication
                        *mult = *mult * ((mult->_value * o._value) / mult->_value);
                        return;
                    }
                }
            }

            _muls.push_back(new Multiplication(o));
            _faList.push_back(_muls.back());
        }
    }

    void Sum::__op(const Variable& o)
    {
        if(_vars.find(o.getSign()) != _vars.end()) {
            // TODO simplify this
            *_vars[o.getSign()] = Variable((*_vars[o.getSign()]).getFactor() + o.getFactor(), o.getSign());
        }
        else {
            _vars[o.getSign()] = new Variable(o);
            _faList.emplace_back(_vars[o.getSign()]);
        }
    }

    void Sum::__op(const Value& o)
    {
        if(_value) {
            *_value += o;
        } else {
            _value = new Value(o);
            _faList.push_back(_value);
        }
    }

    void Sum::__op(const Logarithm& o)
    {
        auto base = const_cast<ArithmeticObject*>(o.getBase());

        if (_logs.contains(base))
            *_logs.at(base) += o;
        else {
            _logs.at(base) = new Logarithm(o);
            _faList.push_back(_logs.at(base));
        }
    }

    std::string Sum::print() const
    {
        std::string result;

        for(auto& elem : _faList) {
            result += elem->print() + " + ";
        }

        // Remove the unnecessary plus sign at the end of the line
        result = result.erase(result.size() - 3, 3);

        return result;
    }

    Sum::~Sum()
    {
        for(auto& elem: _faList)
            delete elem;
    }

}
