#include "NonAssociativeOperator.hh"

namespace MC::FN
{

    bool NonAssociativeOperator::operator==(const NonAssociativeOperator& o) const
    {
        return compare(_rightOp,o._rightOp) and compare(_leftOp,o._leftOp);
    }

    bool NonAssociativeOperator::operator!=(const NonAssociativeOperator& o) const
    {
        return !(*this == o);
    }
}