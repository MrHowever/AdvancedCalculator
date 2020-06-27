#ifndef FUNCTIONS_EQUALITY_TCC
#define FUNCTIONS_EQUALITY_TCC

#include "OperatorFactory.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Equality::Equality(const T& o1, const P& o2) : _first(nullptr), _second(nullptr)
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<typename T, typename P, typename >
    [[nodiscard]] bool operator==(const T& o1, const P& o2)
    {
        return Equality(o1,o2).evaluate(Value(0));
    }

    template<typename T, typename >
    [[nodiscard]] bool operator==(const T& o1, const ArithmeticObject* o2Ptr)
    {
        return Equality(o1,o2Ptr).evaluate(Value(0));
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] bool operator==(const T& first, const P& second)
    {
        return first == Value(second);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] bool operator==(const P& first, const T& second)
    {
        return second == Value(first);
    }

    template<typename T, typename P, typename >
    [[nodiscard]] bool operator!=(const T& o1, const P& o2)
    {
        return !Equality(o1,o2).evaluate(Value(0));
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] bool operator!=(const T& first, const P& second)
    {
        return !(first == Value(second));
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] bool operator!=(const P& first, const T& second)
    {
        return !(second == Value(first));
    }

    template<typename T>
    void Equality::__genOp(const T& o)
    {
        (_first ? _second : _first) = OperatorFactory::copy(&o);
    }
}

#endif //FUNCTIONS_EQUALITY_TCC
