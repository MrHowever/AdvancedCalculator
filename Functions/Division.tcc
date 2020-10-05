#ifndef FUNCTIONS_DIVISION_TCC
#define FUNCTIONS_DIVISION_TCC

namespace MC::FN
{
    template<ArithmeticRef T, ArithmeticRef P>
    Division::Division(const T& o1, const P& o2) : Division()
    {
        _leftOp = PointerWrapper<T>(new T(o1));
        _rightOp = PointerWrapper<P>(new P(o2));
    }
}

#endif //FUNCTIONS_DIVISION_TCC
