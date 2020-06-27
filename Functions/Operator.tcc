#ifndef FUNCTIONS_OPERATOR_TCC
#define FUNCTIONS_OPERATOR_TCC

#include "Operator.hh"

namespace MC::FN
{
    template<Arithmetic T>
    void Operator::invokeOperation(const T& o)
    {
        invokeOperation(&o);
    }
}

#endif //FUNCTIONS_OPERATOR_TCC
