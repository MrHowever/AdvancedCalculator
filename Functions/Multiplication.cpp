//
// Created by mrhowever on 15.02.2020.
//

#include "IncludeLogarithmMap.hh"
#include "Variable.hh"
#include "IncludeArithmeticObject.hh"
#include "OperatorFactory.hh"
#include "OperatorFactory.tcc"
#include "Multiplication.hh"
#include <iostream>

namespace MC::FN
{
    Multiplication::Multiplication() : _sum(nullptr), _div(nullptr), _value(1) {}

    Multiplication::Multiplication(const Multiplication& m) : Multiplication()
    {
        _sum = m._sum ? dynamic_cast<Sum*>(OperatorFactory::copy(m._sum)) : nullptr;
        _div = m._div ? dynamic_cast<Division*>(OperatorFactory::copy(m._div)) : nullptr;
        _value = m._value;
        _logs = m._logs;
        _vars = m._vars;
    }

    ArithmeticType Multiplication::getType() const
    {
        return MUL;
    }

    void Multiplication::simplify()
    {

    }

    Value Multiplication::evaluate(const Value& value) const
    {
        Value result(1);

        result *= _value;
        if(_sum) result *= _sum->evaluate(value);
        if(_div) result *= _div->evaluate(value);

        std::for_each(_logs.begin(), _logs.end(), [&result](auto& elem) {
            std::for_each(elem.second.begin(),elem.second.end(), [&result](auto& subElem){
                result *= subElem.evaluate(result);
            });
        });

        std::for_each(_vars.begin(), _vars.end(), [&result](auto& elem) {
            result *= elem.first.evaluate(result) /*TODO ^ elem.second*/;
        });

        return result;
    }

    std::string Multiplication::print() const
    {
        std::string result;

        if(!_sum && !_div && _logs.empty() && !_vars.empty()) {
            if(_value != 1)
                result += _value.print();

            for(auto& elem : _vars) {
                if(elem.second != 1) {
                    result += "(" + elem.first.print() + "^" + elem.second.print() + ")";
                }
                else {
                    result += elem.first.print();
                }
            }

            return result;
        }

        //TODO this is a pair instead of ArithmeticObject
//        __printList(result, _logs, '*');
        //__printList(result, _vars, '*');

        for(auto& elem : _vars) {
            if(!result.empty())
                result += " * ";

            result += elem.first.print();

            if(elem.second != 1) {
                result += " ^ " + elem.second.print();
            }
        }

        if (_sum) {
            if(result.empty())
                result += "(" + _sum->print() + ")";
            else {
                result += " * (" + _sum->print() + ")";
            }
        }

        if (_div) {
            if(result.empty())
                result += "(" + _div->print() + ")";
            else {
                result += " * (" + _div->print() + ")";
            }
        }

        if (result.empty())
            result = _value.print();
        else {
            if (_value != 1) {
                if (_value < 0) {
                    if (_value == -1)
                        result = "-" + result;
                    else
                        result += " * (" + _value.print() + ")";
                } else
                    result += " * " + _value.print();
            }
        }

        return result;
    }

    bool Multiplication::sameBase(const Multiplication& first, const Multiplication& second)
    {
        return containersEqual(first._logs, second._logs) &&
            first._sum != nullptr and second._sum != nullptr ? first._sum->operator==(*second._sum) : first._sum == second._sum &&
            first._div != nullptr and second._div != nullptr ? first._div->operator==(*second._div) : first._div == second._div &&
            containersEqual(first._vars, second._vars);
    }

    bool Multiplication::operator==(const Multiplication& mul) const
    {
        return Multiplication::sameBase(*this,mul) && _value == mul._value;
    }

    bool Multiplication::operator!=(const Multiplication& o) const
    {
        return !(*this == o);
    }

    Value Multiplication::getValue() const
    {
        return _value;
    }

    template<>
    void Multiplication::__mult(const Division& o)
    {
        if (!_div) {
            _div = new Division(o);
        }
        else {
            if (*_div == o.reverse()) {
                delete(_div);
                _div = nullptr;
            }
            else {
                safeAssign(&_div, new Division(*_div * o));
            }
        }
    }

    template<>
    void Multiplication::__mult(const Logarithm& o)
    {
        //TODO wtf?
        if(_div)
            safeAssign(&_div, new Division(*_div / o));
        else
            _logs[o.getBase()].push_back(o);
    }

    template<>
    void Multiplication::__mult(const Variable& o)
    {
        _vars.find(o) != _vars.end() ? _vars[o] = 1 : _vars[o]++;
    }

    template<>
    void Multiplication::__mult(const Value& o)
    {
        _value *= o;
    }

    template<>
    void Multiplication::__mult(const Sum& o)
    {
        if(!_sum) {
            safeAssign(&_sum, new Sum(o));
        }
        else {
            Sum newSum(Value(0),Value(0));

            for(const auto& firstElem : *_sum) {
                for(const auto& secondElem : o) {
                    Multiplication mult(firstElem,secondElem);
                    newSum = newSum + mult;
                }
            }

            safeAssign(&_sum,new Sum(newSum));
        }
    }

    template<>
    void Multiplication::__mult(const Multiplication& o)
    {
        if(o._div) {
            safeAssign(&_div, new Division(*_div * *o._div));
        }

        //TODO sum*sum=sum
        if(o._sum) {
            Multiplication sumMult = *_sum * *o._sum;
            _sum = nullptr;
            invokeOperation(sumMult);
        }

        _value *= o._value;

        std::for_each(o._vars.begin(), o._vars.end(), [this](auto& e){
            for(int i = 0; e.second > i; i++) {
                __mult(e.first);
            }
        });

        std::for_each(o._logs.begin(),o._logs.end(), [this](auto& e) {
            std::for_each(e.second.begin(), e.second.end(), [this](auto& elem) {
                __mult(elem);
            });
        });
    }

    Division operator*(const Division& first, const Division& second)
    {
        return Multiplication(first.getNom(),second.getNom()) / Multiplication(first.getDenom(),second.getDenom());
    }

    bool Multiplication::isVarMultiple() const
    {
        return _sum == nullptr && _div == nullptr && _logs.empty() && _value != 1 && _vars.size() == 1;
    }

    bool Multiplication::isSumMultiple() const
    {
        return _sum != nullptr && _div == nullptr && _logs.empty() && _value != 1 && _vars.empty();
    }

    bool Multiplication::isDivMultiple() const
    {
        return _sum == nullptr && _div != nullptr && _logs.empty() && _value != 1 && _vars.empty();
    }

    bool Multiplication::isLogMultiple() const
    {
        return _sum == nullptr && _div == nullptr && _logs.size() == 1 && _logs.begin()->second.size() == 1 && _value != 1 && _vars.empty();
    }

    MultiplicationIterator Multiplication::begin() const
    {
        return MultiplicationIterator(*this);
    }

    MultiplicationIterator Multiplication::end() const
    {
        return MultiplicationIterator::end(*this);
    }

    bool Multiplication::erase(const ArithmeticObject* oPtr)
    {
        for(auto it = begin(); it != end(); ++it) {
            if(Equality(*it,oPtr).evaluate(Value(0))) {
                erase(it);
                return true;
            }
        }

        return false;
    }

    void Multiplication::erase(const MultiplicationIterator& it)
    {
        switch(it._currentStructure)
        {
            case 0: _sum = nullptr; break;
            case 1: _div = nullptr; break;
            case 2: _logs.at(it._logsIt->first).erase(it._logsListIt); break;
            case 3: _vars.erase(it._varsIt); break;
            case 4: _value = 1; break;
        }
    }

    bool MultiplicationIterator::_currentItEnd()
    {
        switch(_currentStructure)
        {
            case 0:
            case 1: return true;
            case 2: return _logsIt == _mult._logs.end();
            case 3: return _varsIt == _mult._vars.end();
            case 4: return true;
        }

        return false;
    }

    size_t MultiplicationIterator::structureSize(uint)
    {
        switch(_currentStructure)
        {
            case 0: return _mult._sum != nullptr;
            case 1: return _mult._div != nullptr;
            case 2: return _mult._logs.size();
            case 3: return _mult._vars.size();
            case 4: return 1;
            default: return 0;
        }
    }

    void MultiplicationIterator::advanceIterator()
    {
        switch (_currentStructure)
        {
            case 2:
                _logsListIt++;

                if(_logsListIt == _logsIt->second.end()) {
                    _logsIt++;
                    _logsListIt = _logsIt->second.begin();
                }
                break;

            case 3: _varsIt++; break;
        }
    }

    MultiplicationIterator::MultiplicationIterator(const Multiplication& mult) :
                                                        _mult(mult),
                                                        _currentStructure(0),
                                                        _varsIt(mult._vars.begin()),
                                                        _logsIt(mult._logs.begin()),
                                                        _logsListIt(mult._logs.empty() ?
                                                                    std::list<Logarithm>::const_iterator() :
                                                                    mult._logs.begin()->second.begin())
    {
        // Advance iterator to first elem if sum doesnt exist so first usage wont return null
        if(mult._sum == nullptr) {
            operator++();
        }
    }

    MultiplicationIterator MultiplicationIterator::end(const Multiplication& mult)
    {
        MultiplicationIterator endIt(mult);

        endIt._currentStructure = 5;
        endIt._varsIt = mult._vars.end();
        endIt._logsIt = mult._logs.end();

        return endIt;
    }

    MultiplicationIterator& MultiplicationIterator::operator++()
    {
        advanceIterator();

        if(_currentItEnd()) {
            while(!structureSize(++_currentStructure) && _currentStructure < 5);
        }

        return *this;
    }

    const Operand* MultiplicationIterator::operator*()
    {
        switch(_currentStructure)
        {
            case 0:
                return _mult._sum;

            case 1:
                return _mult._div;

            case 2://TODO write non leaking version
                return new Multiplication(_logsIt->first, &*_logsListIt);

            case 3://TODO write non leaking version and return power here
                return new Variable(_varsIt->first);

            case 4:
                return &_mult._value;
        }
    }

    bool MultiplicationIterator::operator!=(const MultiplicationIterator& it)
    {
        if(_currentStructure != it._currentStructure)
            return true;

        return _varsIt != it._varsIt or _logsIt != it._logsIt or _logsListIt != it._logsListIt;
    }
}
