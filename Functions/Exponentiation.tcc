#ifndef FUNCTIONS_EXPONENTIATION_TCC
#define FUNCTIONS_EXPONENTIATION_TCC

namespace MC::FN
{
    template<typename T, typename P>
    Exponentiation::Exponentiation(const T& o1, const P& o2) : Exponentiation()
    {
       _leftOp = PointerWrapper(new T(o1));
       _rightOp = PointerWrapper(new P(o2));
    }
}

#endif //FUNCTIONS_EXPONENTIATION_TCC
