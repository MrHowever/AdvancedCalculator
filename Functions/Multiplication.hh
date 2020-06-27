#ifndef FUNCTIONS_MULTIPLICATION_HH
#define FUNCTIONS_MULTIPLICATION_HH

#include "EqualityComparable.hh"
#include "Iterable.hh"
#include "Operator.hh"
#include <unordered_map>
#include <list>
#include "Value.hh"
#include "Variable.hh"

namespace MC::FN
{
    class MultiplicationIterator;

    class Multiplication : public EqualityComparable<Multiplication>,
                            public Iterable<MultiplicationIterator>, public Operator {
        class Base {
            Sum* _sum;
            Division* _div;
            std::unordered_map<const ArithmeticObject*, std::list<Logarithm> > _logs;
            std::unordered_map<Variable,Value> _vars;     // TODO powers

            Base();

            bool operator==(const Base&) const;
            template<typename T> bool is() const;

            friend Multiplication;
            friend MultiplicationIterator;
            friend Sum;
        } _base;

        Value _value;

        Multiplication();

        void __op(const Sum&) override;
        void __op(const Multiplication&) override;
        void __op(const Division&) override;
        void __op(const Value&) override;
        void __op(const Variable&) override;
        void __op(const Logarithm&) override;

        bool erase(const ArithmeticObject*) override;

    public:
        template<typename T, typename P> Multiplication(const T&, const P&);

        [[nodiscard]] bool operator==(const Multiplication&) const override;
        [[nodiscard]] bool operator!=(const Multiplication&) const override;

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override { return MUL; }

        [[nodiscard]] MultiplicationIterator begin() const override;
        [[nodiscard]] MultiplicationIterator end() const override;

        friend class Sum;
        friend class MultiplicationIterator;
        friend class Division;
    };

    class MultiplicationIterator {
        const Multiplication& _mult;
        std::unordered_map<const ArithmeticObject*, std::list<Logarithm> >::const_iterator _logsIt;
        std::list<Logarithm>::const_iterator _logsListIt;
        std::unordered_map<Variable,Value>::const_iterator _varsIt;
        uint _currentStructure = 0;

        bool _currentItEnd();
        size_t structureSize(uint);
        void advanceIterator();
    public:
        explicit MultiplicationIterator(const Multiplication&);
        static MultiplicationIterator end(const Multiplication&);

        MultiplicationIterator& operator++();
        const ArithmeticObject* operator*();
        bool operator!=(const MultiplicationIterator&);

        friend class Multiplication;
    };

    template<Arithmetic T, Arithmetic P>
    [[nodiscard]] Multiplication operator*(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Multiplication operator*(const T&, const P&);

    template<Arithmetic T, Primitive P>
    [[nodiscard]] Multiplication operator*(const P&, const T&);

    [[nodiscard]] Division operator*(const Division&, const Division&);
    [[nodiscard]] Variable operator*(const Variable&, const Value&);
    [[nodiscard]] Variable operator*(const Value&, const Variable&);
    template<Primitive P>
    [[nodiscard]] Variable operator*(const Variable&, const P&);
    template<Primitive P>
    [[nodiscard]] Variable operator*(const Value&, const P&);
}

#include "Multiplication.tcc"

#endif //FUNCTIONS_SUM_HH