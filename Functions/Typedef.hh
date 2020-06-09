//
// Created by mrhowever on 27.02.2020.
//

#ifndef FUNCTIONS_TYPEDEF_HH
#define FUNCTIONS_TYPEDEF_HH

#include <memory>
#include <list>

namespace MC::FN
{
    class Sum;
    class Multiplication;
    class Division;
    class Variable;
    class Value;
    class ArithmeticObject;
    class Logarithm;
    class SumIterator;
    class SumSimplificationRoutines;
    template<typename T> class LogarithmMap;

    typedef ArithmeticObject Operand;

    typedef std::unique_ptr<Sum> SumPtr;
    typedef std::unique_ptr<Multiplication> MultiplicationPtr;
    typedef std::unique_ptr<Division> DivisionPtr;
    typedef std::unique_ptr<Operand> OperandPtr;
    typedef std::unique_ptr<Variable> VariablePtr;
    typedef std::unique_ptr<Value> ValuePtr;
    typedef std::unique_ptr<Logarithm> LogPtr;

    typedef std::list<SumPtr> SumPtrList;
    typedef std::list<MultiplicationPtr> MultiplicationPtrList;
    typedef std::list<DivisionPtr> DivisionPtrList;
    typedef std::list<Division> DivList;
    typedef std::list<Sum> SumList;
    typedef std::list<Multiplication> MultList;
    typedef std::list<OperandPtr> OperandPtrList;
    typedef std::list<VariablePtr> VariablePtrList;
    typedef std::list<Variable> VariableList;
    typedef std::list<Value> ValueList;
    typedef std::list<Logarithm> LogarithmList;
}
#endif //FUNCTIONS_TYPEDEF_HH
