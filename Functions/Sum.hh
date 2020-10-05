#ifndef FUNCTIONS_SUM_HH
#define FUNCTIONS_SUM_HH

#include "AssociativeOperator.hh"
#include "ArithmeticPointerWrapper.hh"
#include "ArithmeticObject.hh"
#include "EqualityComparable.hh"

namespace MC::FN
{
    class Sum : public AssociativeOperator {
    public:
        template<ArithmeticRef T> void invokeOperation(const T&);
        void invokeOperation(const ArithmeticPointerWrapper &);

        Sum() = default;
        template<ArithmeticRef T, ArithmeticRef P> Sum(const T&, const P&);
        Sum(const ArithmeticPointerWrapper &, const ArithmeticPointerWrapper &);
        Sum(const Sum&);
        Sum& operator=(const Sum&);

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;

        ~Sum() override;
    };
}

#endif //FUNCTIONS_SUM_HH

#include "Sum.tcc"
