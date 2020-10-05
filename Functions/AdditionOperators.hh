#ifndef FUNCTIONS_ADDITIONOPERATORS_HH
#define FUNCTIONS_ADDITIONOPERATORS_HH

#include "Typedefs.hh"

namespace MC::FN
{

    class Multiplication;
    class Division;
    class Sum;

    typedef PointerWrapper<Division> DivisionPointerWrapper;

    template<ArithmeticRef T, ArithmeticRef P> [[nodiscard]] ArithmeticPointerWrapper operator+(const T& o1, const P& o2);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator+(const T&, const ArithmeticPointerWrapper &);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator+(const ArithmeticPointerWrapper&, const T&);
    [[nodiscard]] ArithmeticPointerWrapper operator+(const ArithmeticPointerWrapper&, const ArithmeticPointerWrapper &);

    template<ArithmeticRef T> [[nodiscard]] DivisionPointerWrapper operator+(const Division&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator+(const Multiplication&, const T&);
    template<ArithmeticRef T> [[nodiscard]] ArithmeticPointerWrapper operator+(const Sum&, const T&);

    // Amibugity resolutions and special cases
    [[nodiscard]] ArithmeticPointerWrapper operator+(const Multiplication&, const Sum&);
    [[nodiscard]] ArithmeticPointerWrapper operator+(const Multiplication&, const Division&);
    [[nodiscard]] ArithmeticPointerWrapper operator+(const Multiplication&, const Multiplication&);

    [[nodiscard]] ArithmeticPointerWrapper operator+(const Sum&, const Multiplication&);
    [[nodiscard]] ArithmeticPointerWrapper operator+(const Sum&, const Sum&);
}

#endif //FUNCTIONS_ADDITIONOPERATORS_HH

#include "AdditionOperators.tcc"