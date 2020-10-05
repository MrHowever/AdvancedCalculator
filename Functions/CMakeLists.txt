    cmake_minimum_required(VERSION 3.16)
    project(Functions)

    set(CMAKE_CXX_STANDARD 20)

    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++2a")

    add_library(Functions Sum.hh Sum.cpp ArithmeticObject.hh InvalidOperationException.hh Typedefs.hh Multiplication.hh Division.hh Variable.hh Value.hh Value.cpp Value.tcc Sum.tcc Multiplication.tcc Multiplication.cpp Division.tcc Division.cpp Variable.cpp ArithmeticType.hh ArithmeticObject.cpp EqualityComparable.hh Exponentiation.cpp Exponentiation.hh Exponentiation.tcc ExpressionParser.cpp ExpressionParser.hh ArithmeticPointerWrapper.hh ArithmeticPointerWrapper.cpp MultiplicationOperators.hh AdditionOperators.hh DivisionOperators.hh ExponentiationOperators.hh MultiplicationOperators.cpp AdditionOperators.cpp DivisionOperators.cpp ExponentiationOperators.cpp MultiplicationOperators.tcc AdditionOperators.tcc DivisionOperators.tcc ExponentiationOperators.tcc AssociativeOperator.cpp AssociativeOperator.hh AssociativeOperator.tcc NonAssociativeOperator.cpp NonAssociativeOperator.hh SortHash.cpp SortHash.hh)

    add_subdirectory(Tests)

    set_target_properties(Functions PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
