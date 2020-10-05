#ifndef FUNCTIONS_SORTHASH_HH
#define FUNCTIONS_SORTHASH_HH

#include <cstdint>
#include "Typedefs.hh"
#include "Multiplication.hh"
#include "Value.hh"
#include "Variable.hh"
#include "Sum.hh"

namespace MC::FN
{
    template<typename T>
    class SortHash {
    public:
        [[nodiscard]] static uint32_t sortHash(const Value&);
        [[nodiscard]] static uint32_t sortHash(const Variable&);
        [[nodiscard]] static uint32_t sortHash(const Exponentiation&);
        [[nodiscard]] static uint32_t sortHash(const Sum&);
        [[nodiscard]] static uint32_t sortHash(const Division&);
        [[nodiscard]] static uint32_t sortHash(const Multiplication&);
        [[nodiscard]] static uint32_t sortHash(const ArithmeticPointerWrapper&);
    };

    template<typename T>
    uint32_t SortHash<T>::sortHash(const ArithmeticPointerWrapper& p)
    {
        switch (p->getType()) {
            case VAL: return SortHash<T>::sortHash(p.toRef<Value>());
            case VAR: return SortHash<T>::sortHash(p.toRef<Variable>());
            case SUM: return SortHash<T>::sortHash(p.toRef<Sum>());
            case MUL: return SortHash<T>::sortHash(p.toRef<Multiplication>());
            case DIV: return SortHash<T>::sortHash(p.toRef<Division>());
            case EXP: return SortHash<T>::sortHash(p.toRef<Exponentiation>());
            default: throw InvalidOperationException("Not implemented");
        }
    }
}


#endif //FUNCTIONS_SORTHASH_HH
