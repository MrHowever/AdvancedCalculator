#include "AssociativeOperator.hh"
#include "Multiplication.hh"
#include "MultiplicationOperators.hh"

namespace MC::FN
{
    AssociativeOperator::iterator AssociativeOperator::begin() const
    {
        return _operands.begin();
    }

    AssociativeOperator::iterator AssociativeOperator::end() const
    {
        return _operands.end();
    }

    AssociativeOperator::size_t AssociativeOperator::size() const
    {
        return _operands.size();
    }

    bool AssociativeOperator::operator==(const AssociativeOperator& ao) const
    {
        using namespace std::ranges;

        if(getType() != ao.getType()) {
            return false;
        }

        if(ao._operands.size() != _operands.size())
            return false;

        return all_of(begin(), end(), [&ao](auto& e1) {
            return any_of(ao.begin(), ao.end(), [&e1](auto& e2) {
                return compare(e1,e2);
            });
        });
    }

    bool AssociativeOperator::operator!=(const AssociativeOperator& ao) const
    {
        return !(*this == ao);
    }

    //TODO make this Multiplication only
    bool AssociativeOperator::contains(const ArithmeticPointerWrapper& o) const
    {
        using namespace std::ranges;

        if(o->getType() == MUL) {
            MultiplicationPointerWrapper mult = o;
            return all_of(mult->begin(), mult->end(), [this](auto& e){
                return contains(e);
            });
        }

        if(o->getType() == VAR) {
            if(any_of(begin(),end(),[&o](auto& e){ return e->getType() == EXP && compare(((ExponentiationPointerWrapper)e)->getBase(),o); })) {
                return true;
            }
        }

        return any_of(begin(),end(),[&o](auto& e){ return compare(e,o); });
    }

    void AssociativeOperator::remove(const ArithmeticPointerWrapper& o)
    {
        if(getType() == o->getType()) {
            for(auto& e : *(MultiplicationPointerWrapper) o) {
                for (auto& elem : *this) {
                    if (compare(elem, e)) {
                        _operands.remove(elem);
                        break;
                    }
                }
            }
        } else {
            for (auto& elem : *this) {
                if (compare(elem, o)) {
                    _operands.remove(elem);
                    break;
                }
            }
        }
    }

    void AssociativeOperator::add(const ArithmeticPointerWrapper& o)
    {
        _operands.push_back(o.copyObject());
    }

    ArithmeticPointerWrapper AssociativeOperator::commonCore(const AssociativeOperator& o1, const AssociativeOperator& o2)
    {
        std::list<ArithmeticPointerWrapper> common;

        if(o1.getType() != o2.getType())
            return nullptr;

        for(auto& e1 : o1) {
            for(auto& e2 : o2) {
                if(compare(e1,e2)) {
                    common.push_back(e1);
                }

                if(e1->getType() == VAL && e2->getType() == VAL) {
                    ValuePointerWrapper val1 = e1;
                    ValuePointerWrapper val2 = e2;
                    common.push_back(*val1 < *val2 ? val1 : val2);
                }
            }
        }

        if(common.empty())
            return ArithmeticPointerWrapper();

        if(common.size() == 1)
            return common.front().copyObject();

        ArithmeticPointerWrapper result = common.front().copyObject();
        common.pop_front();

        std::for_each(common.begin(), common.end(), [&result](auto& e) {
            result = result * e;
        });

        return result;
    }

    void AssociativeOperator::clear()
    {
        for (auto& elem : _operands)
            elem.Delete();

        _operands.clear();

    }

    void AssociativeOperator::copy(const AssociativeOperator& o)
    {
        o.for_each([this](auto& e) { add(e.copyObject()); });
    }
}