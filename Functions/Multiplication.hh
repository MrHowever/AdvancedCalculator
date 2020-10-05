#ifndef FUNCTIONS_MULTIPLICATION_HH
#define FUNCTIONS_MULTIPLICATION_HH

#include "AssociativeOperator.hh"
#include "ArithmeticPointerWrapper.hh"

namespace MC::FN
{
    class Multiplication : public AssociativeOperator {

        [[nodiscard]] ArithmeticPointerWrapper _extractMult(const MultiplicationPointerWrapper&) const;
        [[nodiscard]] ArithmeticPointerWrapper _extractVal(const ValuePointerWrapper&) const;
        [[nodiscard]] ArithmeticPointerWrapper _extractExp(const ExponentiationPointerWrapper &) const;
        [[nodiscard]] ArithmeticPointerWrapper _extractVar(const VariablePointerWrapper &) const;

    public:
        template<ArithmeticRef T> void invokeOperation(const T&);
        void invokeOperation(const ArithmeticPointerWrapper &);

        Multiplication() = default;
        template<ArithmeticRef T, ArithmeticRef P> Multiplication(const T&, const P&);
        Multiplication(const ArithmeticPointerWrapper &, const ArithmeticPointerWrapper &);
        Multiplication(const Multiplication&);
        Multiplication& operator=(const Multiplication&);

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;
        [[nodiscard]] ArithmeticPointerWrapper extract(const ArithmeticPointerWrapper&) const;

        ~Multiplication() override;
    };
}

#endif //FUNCTIONS_SUM_HH

#include "Multiplication.tcc"
