#include "Multiplication.hh"
#include "Sum.hh"
#include "Division.hh"
#include "Logarithm.hh"
#include "Equality.hh"

#include <algorithm>

namespace MC::FN
{
    Multiplication::Base::Base() : _sum(nullptr), _div(nullptr)
    {
        
    }
    
    Multiplication::Multiplication() : _base(), _value(1) {}

//    constexpr ArithmeticType Multiplication::getType() const
//    {
//        return MUL;
//    }

    Value Multiplication::evaluate(const Value& value) const
    {
        Value result(1);
        Variable var('x');

        result *= _value;
        if(_base._sum) result *= _base._sum->evaluate(value);
        if(_base._div) result *= _base._div->evaluate(value);

        std::for_each(_base._logs.begin(), _base._logs.end(), [&result](auto& elem) {
            std::for_each(elem.second.begin(),elem.second.end(), [&result](auto& subElem){
                result *= subElem.evaluate(result);
            });
        });

        std::for_each(_base._vars.begin(), _base._vars.end(), [&result](auto& elem) {
            result *= elem.first.evaluate(result) /*TODO ^ elem.second*/;
        });

        return result;
    }

    std::string Multiplication::print() const
    {
        std::string result;

        if(!_base._sum && !_base._div && _base._logs.empty() && !_base._vars.empty()) {
            if(_value != 1)
                result += _value.print();

            for(auto& elem : _base._vars) {
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
//        __printList(result, _base._logs, '*');
        //__printList(result, _base._vars, '*');

        for(auto& elem : _base._vars) {
            if(!result.empty())
                result += " * ";

            result += elem.first.print();

            if(elem.second != 1) {
                result += " ^ " + elem.second.print();
            }
        }

        if (_base._sum) {
            if(result.empty())
                result += "(" + _base._sum->print() + ")";
            else {
                result += " * (" + _base._sum->print() + ")";
            }
        }

        if (_base._div) {
            if(result.empty())
                result += "(" + _base._div->print() + ")";
            else {
                result += " * (" + _base._div->print() + ")";
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
    
    bool Multiplication::Base::operator==(const Base& second) const
    {
        //TODO wtf
        return /*_logs == second._logs &&*/
               _sum != nullptr and second._sum != nullptr and *_sum == *second._sum &&
               _div != nullptr and second._div != nullptr and *_div == *second._div &&
               _vars == second._vars;
    }

    template<>
    bool Multiplication::Base::is<Sum>() const
    {
        return _logs.empty() and _vars.empty() and !_div and _sum;
    }

    template<>
    bool Multiplication::Base::is<Division>() const
    {
        return _logs.empty() and _vars.empty() and !_sum and _div;
    }

    template<>
    bool Multiplication::Base::is<Logarithm>() const
    {
        return _vars.empty() and !_sum and !_div and _logs.size() == 1 and _logs.begin()->second.size() == 1;
    }

    template<>
    bool Multiplication::Base::is<Variable>() const
    {
        return _logs.empty() and !_sum and !_div and _vars.size() == 1;
    }

    bool Multiplication::operator==(const Multiplication& second) const
    {
        return  _base == second._base && _value == second._value;
    }

    bool Multiplication::operator!=(const Multiplication& o) const
    {
        return !(*this == o);
    }

    void Multiplication::__op(const Division& o)
    {
        if (!_base._div) {
            _base._div = new Division(o);
        }
        else {
            if (*_base._div == o.reverse()) {
                delete(_base._div);
                _base._div = nullptr;
            }
            else {
                safeAssign(&_base._div, new Division(*_base._div * o));
            }
        }
    }

    void Multiplication::__op(const Logarithm& o)
    {
        //TODO wtf?
        if(_base._div)
            safeAssign(&_base._div, new Division(*_base._div / o));
        else
            _base._logs[o.getBase()].push_back(o);
    }

    void Multiplication::__op(const Variable& o)
    {
        _base._vars.find(o) != _base._vars.end() ? _base._vars[o] = 1 : _base._vars[o]++;
    }

    void Multiplication::__op(const Value& o)
    {
        _value *= o;
    }

    void Multiplication::__op(const Sum& o)
    {
        if(!_base._sum) {
            safeAssign(&_base._sum, new Sum(o));
        }
        else {
            Sum newSum(Value(0),Value(0));

            for(const auto& firstElem : *_base._sum) {
                for(const auto& secondElem : o) {
                    Multiplication mult(firstElem,secondElem);
                    newSum = newSum + mult;
                }
            }

            safeAssign(&_base._sum,new Sum(newSum));
        }
    }

    void Multiplication::__op(const Multiplication& o)
    {
        if(o._base._div) {
            safeAssign(&_base._div, new Division(*_base._div * *o._base._div));
        }

        //TODO sum*sum=sum
        if(o._base._sum) {
            Multiplication sumMult = *_base._sum * *o._base._sum;
            _base._sum = nullptr;
            invokeOperation(sumMult);
        }

        _value *= o._value;

        std::for_each(o._base._vars.begin(), o._base._vars.end(), [this](auto& e){
            for(int i = 0; e.second > i; i++) {
                __op(e.first);
            }
        });

        std::for_each(o._base._logs.begin(),o._base._logs.end(), [this](auto& e) {
            std::for_each(e.second.begin(), e.second.end(), [this](auto& elem) {
                __op(elem);
            });
        });
    }

    Division operator*(const Division& first, const Division& second)
    {
        return Multiplication(first.getNom(),second.getNom()) / Multiplication(first.getDenom(),second.getDenom());
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
                switch(it._currentStructure)
                {
                    case 0: _base._sum = nullptr; break;
                    case 1: _base._div = nullptr; break;
                    case 2: _base._logs.at(it._logsIt->first).erase(it._logsListIt); break;
                    case 3: _base._vars.erase(it._varsIt); break;
                    case 4: _value = 1; break;
                }

                return true;
            }
        }

        return false;
    }

    bool MultiplicationIterator::_currentItEnd()
    {
        switch(_currentStructure)
        {
            case 0:
            case 1: return true;
            case 2: return _logsIt == _mult._base._logs.end();
            case 3: return _varsIt == _mult._base._vars.end();
            case 4: return true;
        }

        return false;
    }

    size_t MultiplicationIterator::structureSize(uint)
    {
        switch(_currentStructure)
        {
            case 0: return _mult._base._sum != nullptr;
            case 1: return _mult._base._div != nullptr;
            case 2: return _mult._base._logs.size();
            case 3: return _mult._base._vars.size();
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
                                                        _varsIt(mult._base._vars.begin()),
                                                        _logsIt(mult._base._logs.begin()),
                                                        _logsListIt(mult._base._logs.empty() ?
                                                                    std::list<Logarithm>::const_iterator() :
                                                                    mult._base._logs.begin()->second.begin())
    {
        // Advance iterator to first elem if sum doesnt exist so first usage wont return null
        if(mult._base._sum == nullptr) {
            operator++();
        }
    }

    MultiplicationIterator MultiplicationIterator::end(const Multiplication& mult)
    {
        MultiplicationIterator endIt(mult);

        endIt._currentStructure = 5;
        endIt._varsIt = mult._base._vars.end();
        endIt._logsIt = mult._base._logs.end();

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

    const ArithmeticObject* MultiplicationIterator::operator*()
    {
        switch(_currentStructure)
        {
            case 0:
                return _mult._base._sum;

            case 1:
                return _mult._base._div;

            case 2://TODO write non leaking version
                return new Multiplication(_logsIt->first, &*_logsListIt);

            case 3://TODO write non leaking version and return power here
                return new Variable(_varsIt->first);

            case 4:
                return &_mult._value;

            default: throw InvalidOperationException("Type not handled");
        }
    }

    bool MultiplicationIterator::operator!=(const MultiplicationIterator& it)
    {
        if(_currentStructure != it._currentStructure)
            return true;

        return _varsIt != it._varsIt or _logsIt != it._logsIt or _logsListIt != it._logsListIt;
    }

    Variable operator*(const Variable& var, const Value& val)
    {
        return Variable(val,var.getSign());
    }

    Variable operator*(const Value& val, const Variable& var)
    {
        return Variable(val,var.getSign());
    }
}
