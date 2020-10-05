#ifndef FUNCTIONS_VARIABLE_HH
#define FUNCTIONS_VARIABLE_HH

#include "ArithmeticPointerWrapper.hh"
#include "Value.hh"

namespace MC::FN
{
    class Variable : public ArithmeticObject {
        char _value;
    public:
        explicit Variable(char);

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;
        [[nodiscard]] std::string print() override;

        [[nodiscard]] bool operator==(const Variable&) const;
        [[nodiscard]] bool operator!=(const Variable&) const;

        [[nodiscard]] char getValue() const;
    };
}

#endif //FUNCTIONS_VARIABLE_HH
