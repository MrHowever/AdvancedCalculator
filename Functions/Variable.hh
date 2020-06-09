//
// Created by mrhowever on 30.01.2020.
//

#ifndef FUNCTIONS_VARIABLE_HH
#define FUNCTIONS_VARIABLE_HH

#include "ArithmeticObject.hh"

namespace MC::FN
{
    class Variable : public ArithmeticObject {
        char _value;

    public:
        explicit Variable(char);

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] ArithmeticType getType() const override;
        [[nodiscard]] std::string print() const override;

        [[nodiscard]] bool operator==(const Variable&) const;
        [[nodiscard]] bool operator!=(const Variable&) const;
        [[nodiscard]] bool operator<(const Variable&) const;

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
