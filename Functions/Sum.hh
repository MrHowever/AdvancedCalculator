#ifndef FUNCTIONS_SUM_HH
#define FUNCTIONS_SUM_HH

#include "Operator.hh"
#include "EqualityComparable.hh"
#include "SumIterator.hh"
#include "Iterable.hh"
#include <map>
#include <unordered_map>

namespace MC::FN
{
    class Sum : public Operator, public EqualityComparable<Sum>, public Iterable<SumIterator> {

        // Operands
        Division* _div;
        Value* _value;
        std::list<Multiplication*> _muls;
        std::unordered_map<char, Variable*> _vars;
        std::unordered_map<ArithmeticObject*,Logarithm*> _logs;

        // Fast access list
        std::list<ArithmeticObject*> _faList;

        // Base constructor
        Sum();

        // Operation implementations
        void __op(const Sum&) override;
        void __op(const Multiplication&) override;
        void __op(const Division&) override;
        void __op(const Value&) override;
        void __op(const Variable&) override;
        void __op(const Logarithm&) override;

    public:
        // Public constructor for binary operator
        template<typename T, typename P> Sum(const T&, const P&);
        Sum(const Sum&);

        // Equality operators
        [[nodiscard]] bool operator==(const Sum&) const override;
        [[nodiscard]] bool operator!=(const Sum&) const override;

        // Inherited ArithmeticObject behaviour
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;

        // Inherited Iterable interface
    private:
        bool erase(const ArithmeticObject*) override { return false;} //TODO implement
    public:
        [[nodiscard]] SumIterator begin() const override;
        [[nodiscard]] SumIterator end() const override;

        friend class SumIterator;

        ~Sum() override;
    };

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Sum operator+(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Sum operator+(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Sum operator+(const P&, const T&);

    [[nodiscard]] Division operator+(const Division&, const Division&);
}

#include "Sum.tcc"

#endif //FUNCTIONS_SUM_HH
