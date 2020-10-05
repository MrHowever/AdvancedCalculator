#ifndef FUNCTIONS_SUM_TCC
#define FUNCTIONS_SUM_TCC

#include "Typedefs.hh"
#include "AdditionOperators.hh"

namespace MC::FN
{
    template<ArithmeticRef T, ArithmeticRef P>
    Sum::Sum(const T& o1, const P& o2) : Sum()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<ArithmeticRef T>
    void Sum::invokeOperation(const T& o)
    {
        if constexpr(std::is_same_v<T,Sum>) {
            o.for_each([this](auto& elem) { invokeOperation(elem); } );
            return;
        }

        if (size() > 1) {
            for (auto& elem : *this) {
                auto result = o + elem;

                if (result->getType() != SUM) {
                    remove(elem);
                    add(result);
                    return;
                }
            }
        }

        add(o);
    }
}

#endif //FUNCTIONS_SUM_TCC
