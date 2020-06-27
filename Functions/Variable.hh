#ifndef FUNCTIONS_VARIABLE_HH
#define FUNCTIONS_VARIABLE_HH

#include "ArithmeticObject.hh"
#include "Value.hh"

namespace MC::FN
{
    class Variable : public ArithmeticObject {
        char _value;
        Value _factor;
    public:
        explicit Variable(char);
        Variable(const Value&, char);

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;
        [[nodiscard]] std::string print() const override;

        [[nodiscard]] bool operator==(const Variable&) const;
        [[nodiscard]] bool operator!=(const Variable&) const;
        [[nodiscard]] bool operator<(const Variable&) const;

        [[nodiscard]] char getSign() const;
        [[nodiscard]] Value getFactor() const;

        friend struct std::hash<Variable>;
    };
}

template<>
struct std::hash<MC::FN::Variable>
{
    std::size_t operator()(const MC::FN::Variable& var) const
    {
        return std::hash<char>()(var._value);
    }
};

#endif //FUNCTIONS_VARIABLE_HH
