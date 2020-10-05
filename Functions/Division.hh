//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_DIVISION_HH
#define FUNCTIONS_DIVISION_HH

#include "NonAssociativeOperator.hh"
#include "Typedefs.hh"

namespace MC::FN
{
    class Division : public NonAssociativeOperator {
        // Base constructor
        Division() = default;

    public:
        // Public constructor
        template<ArithmeticRef T, ArithmeticRef P> Division(const T&, const P&);
        Division(const ArithmeticPointerWrapper &, const ArithmeticPointerWrapper &);
        Division(const Division&);
        Division& operator=(const Division&);

        // Inherited methods
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;

        // Members access methods
        [[nodiscard]] const ArithmeticPointerWrapper& getNom() const;
        [[nodiscard]] const ArithmeticPointerWrapper& getDenom() const;

        ~Division() override;
    };
}

#endif //FUNCTIONS_SUM_HH
//TODO self-assignment check
#include "Division.tcc"
