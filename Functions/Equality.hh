#ifndef FUNCTIONS_EQUALITY_HH
#define FUNCTIONS_EQUALITY_HH

#include "ArithmeticObject.hh"
#include "Typedefs.hh"
#include "IncludeValue.hh"

namespace MC::FN
{
    class Equality : public ArithmeticObject {

        ArithmeticObject* _first;
        ArithmeticObject* _second;

        template<typename T> void __compare(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T*);

    public:
        template<typename T, typename P> Equality(const T&, const P&);

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] ArithmeticType getType() const override;
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

