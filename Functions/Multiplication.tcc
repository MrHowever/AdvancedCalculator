#ifndef FUNCTIONS_MULTIPLICATION_TCC
#define FUNCTIONS_MULTIPLICATION_TCC

namespace MC::FN
{
    template<typename T, typename P>
    Multiplication::Multiplication(const T& o1, const P& o2) : Multiplication()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Multiplication operator*(const T& o1, const P& o2)
    {
        return Multiplication(o1,o2);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Multiplication operator*(const T& first, const P& second)
    {
        return first * Value(second);
    }

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Multiplication operator*(const P& first, const T& second)
    {
        return second * Value(first);
    }

    template<typename T>
    bool Multiplication::Base::is() const
    {
        throw InvalidOperationException("Invalid template type");
    }

    template<Primitive P>
    Variable operator*(const Variable& var, const P& val)
    {
        return Variable(Value(val),var.getSign());
    }

    template<Primitive P>
    Variable operator*(const P& val, const Variable& var)
    {
        return Variable(Value(val),var.getSign());
    }
}

#endif //FUNCTIONS_MULTIPLICATION_TCC
