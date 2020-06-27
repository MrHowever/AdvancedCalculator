#include "SumIterator.hh"
#include "Sum.hh"

namespace MC::FN
{

    SumIterator& SumIterator::operator++()
    {
        _it++;
        return *this;
    }

    const ArithmeticObject* SumIterator::operator*()
    {
        return *_it;
    }

    SumIterator::SumIterator(const Sum& sum) : _it(sum._faList.begin())
    {

    }

    bool SumIterator::operator!=(const SumIterator& it)
    {
        return _it != it._it;
    }

    SumIterator SumIterator::end(const Sum& sum)
    {
        SumIterator iter(sum);
        iter._it = sum._faList.end();
        return iter;
    }
}