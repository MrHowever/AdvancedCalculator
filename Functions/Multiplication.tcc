#ifndef FUNCTIONS_MULTIPLICATION_TCC
#define FUNCTIONS_MULTIPLICATION_TCC

#include "Value.hh"

namespace MC::FN
{
    template<ArithmeticRef T, ArithmeticRef P>
    Multiplication::Multiplication(const T& o1, const P& o2) : Multiplication()
    {
        invokeOperation(o1);
        invokeOperation(o2);
    }

    template<ArithmeticRef T>
    void Multiplication::invokeOperation(const T& o)
    {
        if constexpr(std::is_same_v<T,Multiplication>) {
            if(!size()) {
                *this = o;
            } else if(size() == 1) {
                Multiplication mult = o;
                mult.invokeOperation(*begin());
                *this = mult;
            } else {
                for (auto& elem : o) {
                    invokeOperation(elem);
                }
            }

            return;
        }

        if (size() > 1) {
            for (auto& elem : *this) {
                auto result = o * elem;

                if(result->getType() == VAL && compare(result, new Value(1))) {
                        remove(elem);
                        return;
                } else if (result->getType() != MUL) {
                    remove(elem);
                    add(result);
                    return;
                }
            }
        }

        add(o);
    }
}

#endif //FUNCTIONS_MULTIPLICATION_TCC
