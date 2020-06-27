#ifndef FUNCTIONS_SUMITERATOR_HH
#define FUNCTIONS_SUMITERATOR_HH

#include <list>

namespace MC::FN
{
    class Sum;
    class ArithmeticObject;

    class SumIterator {
        std::list<ArithmeticObject*>::const_iterator _it;
    public:
        explicit SumIterator(const Sum&);
        static SumIterator end(const Sum&);

        SumIterator& operator++();
        const ArithmeticObject* operator*();

        bool operator!=(const SumIterator&);
    };
}

#endif //FUNCTIONS_SUMITERATOR_HH
