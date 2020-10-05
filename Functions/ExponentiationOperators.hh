#ifndef FUNCTIONS_EXPONENTIATIONOPERATORS_HH
#define FUNCTIONS_EXPONENTIATIONOPERATORS_HH

#include "Typedefs.hh"

namespace MC::FN
{
    class Value;
    class Exponentiation;

    // Default cases
    template<ArithmeticRef T, ArithmeticRef P> [[nodiscard]] ArithmeticPointerWrapper operator^(const T& o1, const P& o2);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator^(const T&, const ArithmeticPointerWrapper &);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator^(const ArithmeticPointerWrapper&, const T&);
    [[nodiscard]] ArithmeticPointerWrapper operator^(const ArithmeticPointerWrapper&, const ArithmeticPointerWrapper &);

    // General cases
    template<ArithmeticRef T> ArithmeticPointerWrapper operator^(const Exponentiation&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator^(const Value&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator^(const T&, const Value&);

    // Ambiguity resolutions and special cases
    [[nodiscard]] ArithmeticPointerWrapper operator^(const Exponentiation&, const Value&);
    [[nodiscard]] ArithmeticPointerWrapper operator^(const Value&, const Exponentiation&);
}

#endif //FUNCTIONS_EXPONENTIATIONOPERATORS_HH

#include "ExponentiationOperators.tcc"