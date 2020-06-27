    cmake_minimum_required(VERSION 3.16)
    project(Functions)

    set(CMAKE_CXX_STANDARD 20)

    add_library(Functions Sum.hh Sum.cpp ArithmeticObject.hh InvalidOperationException.hh Typedefs.hh Multiplication.hh Division.hh Logarithm.hh Logarithm.cpp Variable.hh Value.hh Value.cpp Value.tcc Sum.tcc Multiplication.tcc Multiplication.cpp Division.tcc Division.cpp Logarithm.cpp Variable.cpp ArithmeticType.hh Equality.cpp Equality.hh Equality.tcc ArithmeticObject.cpp ArithmeticObject.tcc OperatorFactory.hh EqualityComparable.cpp EqualityComparable.hh Iterable.hh Operator.hh Operator.cpp Operator.tcc SumIterator.cpp SumIterator.hh)

    add_subdirectory(Tests)

    set_target_properties(Functions PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
