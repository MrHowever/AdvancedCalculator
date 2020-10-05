#include "SortHash.hh"

namespace MC::FN
{
    /*
     *                  MULTIPLICATION
     */
    
    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Value& val)
    {
        return 0;
    }

    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Variable& var)
    {
        return var.getValue() - 'a' + 1;
    }

    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Exponentiation& exp)
    {
        return 34;
    }

    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Sum& sum)
    {
        return 34;
    }

    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Multiplication& mul)
    {
        return 34;
    }

    template<>
    uint32_t SortHash<Multiplication>::sortHash(const Division& div)
    {
        return 34;
    }
    
    /*
     *                  SUM
     */

    template<>
    uint32_t SortHash<Sum>::sortHash(const Value& val)
    {
        return std::numeric_limits<uint32_t>::max();
    }

    template<>
    uint32_t SortHash<Sum>::sortHash(const Variable& var)
    {
        return var.getValue() - 'a' + 1;
    }

    template<>
    uint32_t SortHash<Sum>::sortHash(const Exponentiation& exp)
    {
        return 34;
    }

    template<>
    uint32_t SortHash<Sum>::sortHash(const Sum& sum)
    {
        return 34;
    }

    template<>
    uint32_t SortHash<Sum>::sortHash(const Multiplication& mul)
    {
        if(mul.size() == 2) {
            auto first = (*mul.begin());
            auto second = (*++mul.begin());

            if((first->getType() == VAR && second->getType() == VAL)) {
                return SortHash<Sum>::sortHash(first);
            }

            if((first->getType() == VAL && second->getType() == VAR)) {
                return SortHash<Sum>::sortHash(second);
            }
        }

        return 34 + mul.size();
    }

    template<>
    uint32_t SortHash<Sum>::sortHash(const Division& div)
    {
        return 34;
    }
}