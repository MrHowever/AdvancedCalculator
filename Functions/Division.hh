//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_DIVISION_HH
#define FUNCTIONS_DIVISION_HH

#include "ArithmeticObject.hh"
#include "Typedefs.hh"
#include "Typedef.hh"

namespace MC::FN
{
    class Division : public ArithmeticObject {

        // Members
        ArithmeticObject* _nom;
        ArithmeticObject* _denom;

        // Base constructor
        Division();

        // Internal helper methods
        template<typename T> void _div(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T*);

    public:
        // Public constructor
        template<typename T, typename P> Division(const T&, const P&);

        // Equality operators
        [[nodiscard]] bool operator==(const Division&) const;
        [[nodiscard]] bool operator!=(const Division&) const;

        // Inherited methods
        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] ArithmeticType getType() const override;

        // Members access methods
        [[nodiscard]] Division reverse() const;
        [[nodiscard]] const ArithmeticObject* getNom() const;
        [[nodiscard]] const ArithmeticObject* getDenom() const;

        ~Division() override;
    };

    template<typename T, typename P, typename = EnableIfAreArithmetic<T,P>>
    [[nodiscard]] Division operator/(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Division operator/(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Division operator/(const P&, const T&);
}

#endif //FUNCTIONS_SUM_HH
