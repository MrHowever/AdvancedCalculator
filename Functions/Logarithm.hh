#ifndef FUNCTIONS_LOGARITHM_HH
#define FUNCTIONS_LOGARITHM_HH

#include "ArithmeticObject.hh"

namespace MC::FN
{
    class Logarithm : public ArithmeticObject {
        ArithmeticObject* _base;
        ArithmeticObject* _operand;

    public:
        //TODO make private
        Logarithm();
        // TODO copy and swap idiom??
        Logarithm(const Logarithm&);
        Logarithm& operator=(const Logarithm&);

        [[nodiscard]] const ArithmeticObject* getBase() const;

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override { return LOG; }
        [[nodiscard]] std::string print() const override;

        Logarithm operator+(const Logarithm&) const;
        Logarithm& operator+=(const Logarithm&);

        [[nodiscard]] bool operator==(const Logarithm&) const;
        [[nodiscard]] bool operator!=(const Logarithm&) const;
    };
}

#endif //FUNCTIONS_SUM_HH
