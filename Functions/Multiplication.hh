#ifndef FUNCTIONS_MULTIPLICATION_HH
#define FUNCTIONS_MULTIPLICATION_HH

#include "LogarithmMap.hh"
#include "IncludeValue.hh"

namespace MC::FN
{
    typedef LogarithmMap<LogarithmList> LogarithmMultiplicationMap;
    class MultiplicationIterator;

    class Multiplication : public ArithmeticObject {

        Sum* _sum;
        Division* _div;
        std::unordered_map<const ArithmeticObject*, std::list<Logarithm> > _logs;
        std::unordered_map<Variable,Value> _vars;     // TODO powers
        Value _value;

        Multiplication();

        template<typename T> void __mult(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T> > void invokeOperation(const T*);
    public:
        template<typename T, typename P> Multiplication(const T&, const P&);
        Multiplication(const Multiplication&);

        [[nodiscard]] bool operator==(const Multiplication&) const;
        [[nodiscard]] bool operator!=(const Multiplication&) const;

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] ArithmeticType getType() const override;

        [[nodiscard]] MultiplicationIterator begin() const;
        [[nodiscard]] MultiplicationIterator end() const;

        void erase(const MultiplicationIterator&);
        bool erase(const ArithmeticObject*);

        static bool sameBase(const Multiplication&, const Multiplication&);
        Value getValue() const;
        bool isVarMultiple() const;
        bool isSumMultiple() const;
        bool isDivMultiple() const;
        bool isLogMultiple() const;

        friend class Sum;
        friend class MultiplicationIterator;
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
        const Operand* operator*();
        bool operator!=(const MultiplicationIterator&);

        friend class Multiplication;
    };

    template<typename T, typename P, typename = EnableIfAreArithmetic<T,P>>
    [[nodiscard]] Multiplication operator*(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Multiplication operator*(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Multiplication operator*(const P&, const T&);

    Division operator*(const Division&, const Division&);
}

#include "Multiplication.tcc"

#endif //FUNCTIONS_SUM_HH