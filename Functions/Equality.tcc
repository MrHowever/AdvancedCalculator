#ifndef FUNCTIONS_EQUALITY_TCC
#define FUNCTIONS_EQUALITY_TCC

#include "OperatorFactory.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Equality::Equality(const T& o1, const P& o2)
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

    template<typename T, typename>
    void Equality::invokeOperation(const T& o)
    {
        __compare(o);
    }

    template<typename T, typename>
    void Equality::invokeOperation(const T* o)
    {
        switch(o->getType())
        {
            case SUM: invokeOperation(dynamic_cast<const Sum&>(*o));            break;
            case MUL: invokeOperation(dynamic_cast<const Multiplication&>(*o)); break;
            case DIV: invokeOperation(dynamic_cast<const Division&>(*o));       break;
            case LOG: invokeOperation(dynamic_cast<const Logarithm&>(*o));      break;
            case VAR: invokeOperation(dynamic_cast<const Variable&>(*o));       break;
            case VAL: invokeOperation(dynamic_cast<const Value&>(*o));          break;
        }
    }

    template<typename T>
    void Equality::__compare(const T& o)
    {
        _first ? _second : _first = OperatorFactory::copy(&o);
    }
}

#endif //FUNCTIONS_EQUALITY_TCC
