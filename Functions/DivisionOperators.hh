#ifndef FUNCTIONS_DIVISIONOPERATORS_HH
#define FUNCTIONS_DIVISIONOPERATORS_HH

#include "Typedefs.hh"

namespace MC::FN
{
    class Multiplication;
    class Division;
    class Sum;
    class Value;
    class Exponentiation;
    class Variable;

    typedef PointerWrapper<Division> DivisionPointerWrapper;

    // Default cases
    template<ArithmeticRef T, ArithmeticRef P> [[nodiscard]] ArithmeticPointerWrapper operator/(const T& o1, const P& o2);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const T&, const ArithmeticPointerWrapper &);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const ArithmeticPointerWrapper&, const T&);
    [[nodiscard]] ArithmeticPointerWrapper operator/(const ArithmeticPointerWrapper&, const ArithmeticPointerWrapper &);

    // General cases
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const T&, const Value&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const Multiplication&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const T&, const Multiplication&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const Division&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator/(const T&, const Division&);

    // Ambiguity resolutions and special cases
    [[nodiscard]] ArithmeticPointerWrapper operator/(const Multiplication&, const Multiplication&);
    [[nodiscard]] ArithmeticPointerWrapper operator/(const Multiplication&, const Division&);
    [[nodiscard]] DivisionPointerWrapper operator/(const Multiplication&, const Exponentiation&);
    [[nodiscard]] ArithmeticPointerWrapper operator/(const Multiplication&, const Value&);

    [[nodiscard]] DivisionPointerWrapper operator/(const Exponentiation&, const Multiplication&);
    [[nodiscard]] DivisionPointerWrapper operator/(const Exponentiation&, const Variable&);
    [[nodiscard]] DivisionPointerWrapper operator/(const Exponentiation&, const Exponentiation&);

    [[nodiscard]] DivisionPointerWrapper operator/(const Variable&, const Exponentiation&);

    [[nodiscard]] DivisionPointerWrapper operator/(const Division&, const Division&);
    [[nodiscard]] DivisionPointerWrapper operator/(const Division&, const Multiplication&);
    [[nodiscard]] DivisionPointerWrapper operator/(const Division&, const Value&);
}

#endif //FUNCTIONS_DIVISIONOPERATORS_HH

#include "DivisionOperators.tcc"