#ifndef FUNCTIONS_SUM_TCC
#define FUNCTIONS_SUM_TCC

namespace MC::FN
{
    template<typename T, typename P>
    Sum::Sum(const T& o1, const P& o2) : Sum()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Sum operator+(const T& o1, const P& o2)
    {
        return Sum(o1,o2);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Sum operator+(const T& first, const P& second)
    {
        return first + Value(second);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Sum operator+(const P& first, const T& second)
    {
        return second + Value(first);
    }

    //TODO  handle built-in arithmetic types
}
#endif //FUNCTIONS_SUM_TCC
