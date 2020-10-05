#ifndef FUNCTIONS_EXPONENTIATION_HH
#define FUNCTIONS_EXPONENTIATION_HH

#include "Typedefs.hh"
#include "NonAssociativeOperator.hh"

namespace MC::FN
{
    class Exponentiation : public NonAssociativeOperator {
        // Base constructor
        Exponentiation() = default;

    public:
        template<typename T, typename P> Exponentiation(const T&, const P&);
        Exponentiation(const ArithmeticPointerWrapper &, const ArithmeticPointerWrapper &);
        Exponentiation(const Exponentiation&);
        Exponentiation& operator=(const Exponentiation&);

        // Inherited methods
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;

        [[nodiscard]] const ArithmeticPointerWrapper& getBase() const;
        [[nodiscard]] const ArithmeticPointerWrapper& getPower() const;

        ~Exponentiation() override;
    };
}

#endif //FUNCTIONS_EXPONENTIATION_HH

#include "Exponentiation.tcc"