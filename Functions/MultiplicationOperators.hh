#ifndef FUNCTIONS_MULTIPLICATIONOPERATORS_HH
#define FUNCTIONS_MULTIPLICATIONOPERATORS_HH

#include "Typedefs.hh"

namespace MC::FN
{
    class Multiplication;
    class Division;
    class Variable;
    class Value;
    class Sum;
    class Exponentiation;

    // Default cases
    template<ArithmeticRef T, ArithmeticRef P> [[nodiscard]] ArithmeticPointerWrapper operator*(const T&, const P&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const T&, const ArithmeticPointerWrapper &);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const ArithmeticPointerWrapper&, const T&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const ArithmeticPointerWrapper&, const ArithmeticPointerWrapper &);

    // General rules
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const Division&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const Value&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const Exponentiation&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const Sum&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator*(const Multiplication&, const T&);

    // Ambiguity resolutions and special cases
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Exponentiation&, const Division&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Exponentiation&, const Sum&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Exponentiation&, const Multiplication&);

    [[nodiscard]] ArithmeticPointerWrapper operator*(const Multiplication&, const Multiplication&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Multiplication&, const Sum&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Multiplication&, const Value&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Multiplication&, const Division&);

    [[nodiscard]] ArithmeticPointerWrapper operator*(const Sum&, const Multiplication&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Sum&, const Sum&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Sum&, const Value&);

    [[nodiscard]] ArithmeticPointerWrapper operator*(const Value&, const Multiplication&);
    [[nodiscard]] ArithmeticPointerWrapper operator*(const Value&, const Sum&);

    [[nodiscard]] ArithmeticPointerWrapper operator*(const Division&, const Multiplication&);
}

#endif //FUNCTIONS_MULTIPLICATIONOPERATORS_HH

#include "MultiplicationOperators.tcc"