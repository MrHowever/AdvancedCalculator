#ifndef FUNCTIONS_NONASSOCIATIVEOPERATOR_HH
#define FUNCTIONS_NONASSOCIATIVEOPERATOR_HH

#include "ArithmeticObject.hh"
#include "ArithmeticPointerWrapper.hh"
#include "EqualityComparable.hh"

namespace MC::FN
{
    class NonAssociativeOperator : public ArithmeticObject, public EqualityComparable<NonAssociativeOperator> {
    protected:
        ArithmeticPointerWrapper _rightOp;
        ArithmeticPointerWrapper  _leftOp;

    public:
        [[nodiscard]] bool operator==(const NonAssociativeOperator&) const override;
        [[nodiscard]] bool operator!=(const NonAssociativeOperator&) const override;

    };
}


#endif //FUNCTIONS_NONASSOCIATIVEOPERATOR_HH
