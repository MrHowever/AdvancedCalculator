#include "Operator.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Variable.hh"
#include "Value.hh"
#include "Logarithm.hh"

namespace MC::FN
{
    void Operator::invokeOperation(const ArithmeticObject* o)
    {
        switch(o->getType())
        {
            case SUM: __op(*dynamic_cast<const Sum*>(o));            break;
            case MUL: __op(dynamic_cast<const Multiplication&>(*o)); break;
            case DIV: __op(dynamic_cast<const Division&>(*o));       break;
            case LOG: __op(dynamic_cast<const Logarithm&>(*o));      break;
            case VAR: __op(dynamic_cast<const Variable&>(*o));       break;
            case VAL: __op(dynamic_cast<const Value&>(*o));          break;
        }
    }
}