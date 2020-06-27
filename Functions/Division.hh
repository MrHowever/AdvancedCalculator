//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_DIVISION_HH
#define FUNCTIONS_DIVISION_HH

#include "Operator.hh"
#include "EqualityComparable.hh"

namespace MC::FN
{
    class Division : public Operator, public EqualityComparable<Division> {

        // Members
        ArithmeticObject* _nom;
        ArithmeticObject* _denom;

        // Base constructor
        Division();

        template<typename T> void __genOp(const T&);

        // Internal helper methods
        void __op(const Sum&) override;
        void __op(const Multiplication&) override;
        void __op(const Division&) override;
        void __op(const Value&) override;
        void __op(const Variable&) override;
        void __op(const Logarithm&) override;

        void simplify();
    public:
        // Public constructor
        template<typename T, typename P> Division(const T&, const P&);

        // Equality operators
        [[nodiscard]] bool operator==(const Division&) const override;
        [[nodiscard]] bool operator!=(const Division&) const override;

        // Inherited methods
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override { return DIV; }

        // Members access methods
        [[nodiscard]] Division reverse() const;
        [[nodiscard]] const ArithmeticObject* getNom() const;
        [[nodiscard]] const ArithmeticObject* getDenom() const;

        ~Division() override;
    };

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Division operator/(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Division operator/(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Division operator/(const P&, const T&);
}

#include "Division.tcc"

#endif //FUNCTIONS_SUM_HH
