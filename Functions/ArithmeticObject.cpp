#include "ArithmeticObject.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"
#include "Exponentiation.hh"
#include "Value.hh"
#include "Variable.hh"

namespace MC::FN
{
    std::ostream& operator<<(std::ostream& strm, ArithmeticObject& obj)
    {
        return strm << obj.print();
    }

    std::string addBraces(const std::string& in)
    {
        return "(" +  in + ")";
    }

    bool compare(const ArithmeticPointerWrapper& o1, const ArithmeticPointerWrapper& o2)
    {
        if(o1->getType() != o2->getType())
            return false;

        switch(o1->getType())
        {
            case SUM: return dynamic_cast<const Sum&>(*o1) ==  dynamic_cast<const Sum&>(*o2);
            case MUL:return dynamic_cast<const Multiplication&>(*o1) == dynamic_cast<const Multiplication&>(*o2);
            case DIV:return dynamic_cast<const Division&>(*o1) == dynamic_cast<const Division&>(*o2);
            case VAR:return dynamic_cast<const Variable&>(*o1) == dynamic_cast<const Variable&>(*o2);
            case VAL:return dynamic_cast<const Value&>(*o1) == dynamic_cast<const Value&>(*o2);
            case EXP:return dynamic_cast<const Exponentiation&>(*o1) == dynamic_cast<const Exponentiation&>(*o2);
            default: throw InvalidOperationException("Implementation missing");
        }
    }
}