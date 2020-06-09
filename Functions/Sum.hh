//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_SUM_HH
#define FUNCTIONS_SUM_HH

#include <string>
#include <functional>
#include "ArithmeticObject.hh"
#include "Typedef.hh"
#include "Typedefs.hh"
#include "LogarithmMap.hh"
#include "Value.hh"
#include "Variable.hh"

namespace MC::FN
{
    typedef LogarithmMap<Logarithm> LogarithmAdditionMap;

    class Sum : public ArithmeticObject {

        LogarithmAdditionMap  _logs;
        std::list<Multiplication> _muls;
        Division*  _div;
        std::unordered_map<Variable, Value> _vars;
        Value _value;

        Sum();

        template<typename T> void __add(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T&);
        template<typename T, typename = EnableIfIsArithmetic<T>> void invokeOperation(const T*);

    public:
        template<typename T, typename P> Sum(const T&, const P&);

        [[nodiscard]] bool operator==(const Sum&) const;
        [[nodiscard]] bool operator!=(const Sum&) const;

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] std::string print() const override;
        [[nodiscard]] ArithmeticType getType() const override;

        [[nodiscard]] SumIterator begin() const;
        [[nodiscard]] SumIterator end() const;

        ~Sum();

        friend SumIterator;
    };

    class SumIterator {
        const Sum& _sum;
        std::unordered_map<Variable,Value>::const_iterator _varIt;
        std::list<Multiplication>::const_iterator _multIt;
        std::map<ArithmeticObject*,Logarithm>::const_iterator _logIt;
        uint _currentStructure = 0;

        bool _currentItEnd();
        size_t structureSize(uint);
        void advanceIterator();
    public:
        explicit SumIterator(const Sum&);
        static SumIterator end(const Sum&);

        SumIterator& operator++();
        const Operand* operator*();
        bool operator!=(const SumIterator&);
    };

    template<typename T, typename P, typename = EnableIfAreArithmetic<T,P>>
    [[nodiscard]] Sum operator+(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Sum operator+(const T&, const P&);

    template<typename T, typename P, typename = EnableIfIsArithmetic<T>, typename = EnableIfPrimitive<P>>
    [[nodiscard]] Sum operator+(const P&, const T&);

    [[nodiscard]] Division operator+(const Division&, const Division&);
}

#endif //FUNCTIONS_SUM_HH
