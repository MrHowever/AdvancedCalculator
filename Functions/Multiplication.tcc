#ifndef FUNCTIONS_MULTIPLICATION_TCC
#define FUNCTIONS_MULTIPLICATION_TCC

#include "Multiplication.hh"
#include "Logarithm.hh"
#include "IncludeDivision.hh"
#include "Equality.hh"

namespace MC::FN
{
    template<typename T, typename P>
    Multiplication::Multiplication(const T& o1, const P& o2) : Multiplication()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<typename T, typename P, typename>
    [[nodiscard]] Multiplication operator*(const T& o1, const P& o2)
    {
        return Multiplication(o1,o2);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Multiplication operator*(const T& first, const P& second)
    {
        return first * Value(second);
    }

    template<typename T, typename P, typename, typename>
    [[nodiscard]] Multiplication operator*(const P& first, const T& second)
    {
        return second * Value(first);
    }

    template<typename T>
    void Multiplication::__mult(const T&)
    {
        throw InvalidOperationException("Unhandled type for multiplication!");
    }

    template<typename T, typename>
    void Multiplication::invokeOperation(const T& o)
    {
        __mult(o);
    }

    template<typename T, typename>
    void Multiplication::invokeOperation(const T* o)
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
}

#endif //FUNCTIONS_MULTIPLICATION_TCC
