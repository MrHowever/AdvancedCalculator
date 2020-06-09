#include "IncludeSum.hh"
#include "Variable.hh"
#include "Logarithm.hh"
#include "IncludeArithmeticObject.hh"
#include "Multiplication.hh"

namespace MC::FN
{
    Sum::Sum() : _value(0), _div(nullptr)
    {
    }

    ArithmeticType Sum::getType() const
    {
        return SUM;
    }

    std::string Sum::print() const
    {
        std::string result;

        //TODO
//        __printList(result, _logs, '+');
        __printList(result, _muls, '+');

        if(_div) {
            if(!result.empty())
                result += " + ";

            result += _div->print();
        }

        if(!result.empty() && !_vars.empty())
            result += " + ";

        for(auto& elem : _vars) {
            if(_vars.find(elem.first) != _vars.begin())
                result += " + ";

            if(elem.second != Value(1))
                result += elem.second.print();

            result += elem.first.print();
        }

        if(_value > 0)
            result += " + " + _value.print();
        else if(_value < 0)
            result += _value.print();

        return result;
    }

    Value Sum::evaluate(const Value& val) const
    {
        Value result(0);

        std::for_each(_logs.begin(), _logs.end(), [&result,&val](auto& elem) {
            result += elem.second.evaluate(val);
        });

        std::for_each(_muls.begin(), _muls.end(), [&result,&val](auto& elem) {
            result += elem.evaluate(val);
        });

        std::for_each(_vars.begin(), _vars.end(), [&result,&val](auto& elem) {
            result += elem.first.evaluate(val) * elem.second;
        });

        result += _div->evaluate(val);
        result += _value;

        return result;
    }

    void Sum::simplify()
    {
        
    }

    bool Sum::operator==(const Sum& sum) const
    {
        return containersEqual(_logs, sum._logs) &&
               containersEqual(_muls, sum._muls) &&
               containersEqual(_vars, sum._vars) &&
               *_div == *sum._div &&
               _value == sum._value;
    }

    bool Sum::operator!=(const Sum& o) const
    {
        return !(*this == o);
    }

    SumIterator Sum::begin() const
    {
        return SumIterator(*this);
    }

    SumIterator Sum::end() const
    {
        return SumIterator::end(*this);
    }

    Sum::~Sum()
    {
        if(_div)
            delete(_div);
    }

    Division operator+(const Division& first, const Division& second)
    {
        return (Multiplication(first.getNom(),second.getDenom()) + Multiplication(second.getNom(),first.getDenom())) /
                        Multiplication(first.getDenom(),second.getDenom());
    }

    bool SumIterator::_currentItEnd()
    {
        switch(_currentStructure)
        {
            case 0: return true;
            case 1: return _varIt  == _sum._vars.end();
            case 2: return _multIt == _sum._muls.end();
            case 3: return true;
            case 4: return _logIt == _sum._logs.end();
        }

        return false;
    }

    void SumIterator::advanceIterator()
    {
        switch(_currentStructure)
        {
            case 1: _varIt++; break;
            case 2: _multIt++; break;
            case 4: _logIt++; break;
        }
    }

    SumIterator& SumIterator::operator++()
    {
        advanceIterator();

        if(_currentItEnd()) {
            while(!structureSize(++_currentStructure) && _currentStructure < 5);
        }

        return *this;
    }

    size_t SumIterator::structureSize(uint structureIdx)
    {
        switch(_currentStructure)
        {
            case 0:  return 1;
            case 1:  return _sum._vars.size();
            case 2:  return _sum._muls.size();
            case 3:  return _sum._div != nullptr;
            case 4:  return _sum._logs.size();
            default: return 0;
        }
    }

    const Operand* SumIterator::operator*()
    {
        switch(_currentStructure)
        {
            case 0:
                return const_cast<Value*>(&_sum._value);

                //TODO write non leaking version
            case 1:
                return new Multiplication(_varIt->first,_varIt->second);

            case 2:
                return const_cast<Multiplication*>(&*_multIt);

            case 3:
                return _sum._div;

            case 4:
                return const_cast<Logarithm*>(&_logIt->second);
        }

        throw InvalidOperationException("Implementation error");
    }

    SumIterator::SumIterator(const Sum& sum) : _sum(sum),
                                               _varIt(sum._vars.begin()),
                                               _multIt(sum._muls.begin()),
                                               _logIt(sum._logs.begin())
    {

    }

    bool SumIterator::operator!=(const SumIterator& it)
    {
        if(_currentStructure != it._currentStructure)
            return true;

        return _varIt != it._varIt or _multIt != it._multIt or _logIt != it._logIt;
    }

    SumIterator SumIterator::end(const Sum& sum)
    {
        SumIterator endIt(sum);

        endIt._currentStructure = 5;
        endIt._varIt = sum._vars.end();
        endIt._multIt = sum._muls.end();
        endIt._logIt = sum._logs.end();

        return endIt;
    }

    template<>
    void Sum::__add(const Division& o)
    {
        _div ? safeAssign(&_div,new Division(*_div + o)) : safeAssign(&_div, new Division(o));
    }

    template<>
    void Sum::__add(const Sum& o)
    {
        std::for_each(o._logs.begin(), o._logs.end(), [this](auto& e) {
            _logs.add(e.second);
        });

        std::for_each(o._vars.begin(), o._vars.end(), [this](auto& e) {
            if(_vars.find(e.first) != _vars.end())
                _vars[e.first] += e.second;
            else
                _vars[e.first] = e.second;
        });

        _muls.insert(_muls.end(), o._muls.begin(), o._muls.end());
        _value += o._value;

        if(o._div) {
            __add(*o._div);
        }
    }

    //TODO value * division = division

    template<>
    void Sum::__add(const Multiplication& o)
    {
        if(o.isVarMultiple()) {
            auto varIt = _vars.find(o._vars.begin()->first);

            if(varIt != _vars.end())
                varIt->second += o._value;
            else
                _vars.insert({o._vars.begin()->first, o._value});
        }
        else if(o.isSumMultiple()) {
            for(int i = 0; o._value > i; i++) {
                __add(*o._sum);
            }
        }
        else if(o.isLogMultiple()) {
            Logarithm tempLog = o._logs.begin()->second.front();
            //TODO 2*log(x) -> log(2x) -> __add(log2x)
        }
        else {
            for (auto& mult : _muls) {
                if (Multiplication::sameBase(mult, o)) {
                    // Retarded way of avoiding new functions to add value to multiplication
                    mult = mult * ((mult.getValue() * o.getValue()) / mult.getValue());
                    return;
                }
            }

            _muls.push_back(o);
        }
    }

    template<>
    void Sum::__add(const Variable& o)
    {
        if(_vars.find(o) != _vars.end()) {
            _vars[o] += 1;
        }
        else {
            _vars[o] = 1;
        }
    }

    template<>
    void Sum::__add(const Value& o)
    {
        _value += o;
    }

    template<>
    void Sum::__add(const Logarithm& o)
    {
        _logs.add(o);
    }
}
