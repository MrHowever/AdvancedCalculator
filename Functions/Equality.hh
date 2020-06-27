#ifndef FUNCTIONS_EQUALITY_HH
#define FUNCTIONS_EQUALITY_HH

#include "Operator.hh"

namespace MC::FN
{
    class Equality : public Operator {

        ArithmeticObject* _first;
        ArithmeticObject* _second;

        template<typename T> void __genOp(const T&);
        void __op(const Sum&) override;
        void __op(const Multiplication&) override;
        void __op(const Division&) override;
        void __op(const Value&) override;
        void __op(const Variable&) override;
        void __op(const Logarithm&) override;


    public:
        template<typename T, typename P> Equality(const T&, const P&);

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override { return EQ; }
   };

    template<typename T, typename P, typename = EnableIfAreArithmetic<T,P>>
    [[nodiscard]] bool operator==(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] bool operator==(const T&, const P&);

    template<typename T, typename = EnableIfIsArithmetic<T>>
    [[nodiscard]] bool operator==(const T&, ArithmeticObject*);

    template<typename T, typename = EnableIfIsArithmetic<T>>
    [[nodiscard]] bool operator!=(const T&, ArithmeticObject*);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] bool operator==(const P&, const T&);

    template<typename T, typename P, typename = EnableIfAreArithmetic<T,P>>
    [[nodiscard]] bool operator!=(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] bool operator!=(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] bool operator!=(const P&, const T&);
}

#include "Equality.tcc"

#endif //FUNCTIONS_EQUALITY_HH

