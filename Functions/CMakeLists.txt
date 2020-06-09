cmake_minimum_required(VERSION 3.14)
project(Functions)

set(CMAKE_CXX_STANDARD 17)

find_library(LIB_TO_INCLUDE TypeTraits /home/mrhowever/Programming/Projects/TypeTraits/lib)
find_library(BO_LIB BasicOperations /home/mrhowever/Programming/Projects/BasicOperations/lib)
find_library(IF_LIB Interfaces /home/mrhowever/Programming/Projects/Interfaces/lib)
include_directories(/home/mrhowever/Programming/Projects/TypeTraits/include /home/mrhowever/Programming/Projects/BasicOperations/include /home/mrhowever/Programming/Projects/Interfaces/include)

add_library(Functions Sum.hh Sum.cpp ArithmeticObject.hh InvalidOperationException.hh Typedefs.hh Multiplication.hh Division.hh Logarithm.hh Logarithm.cpp Variable.hh Value.cpp Value.hh LogarithmMap.tcc LogarithmMap.hh Value.tcc Sum.tcc Multiplication.tcc Multiplication.cpp Division.tcc Division.cpp Logarithm.cpp Variable.cpp ArithmeticType.hh Equality.cpp Equality.hh Equality.tcc ArithmeticObject.cpp IncludeSum.hh IncludeMultiplication.hh IncludeDivision.hh IncludeLogarithmMap.hh Typedef.hh IncludeValue.hh ArithmeticObject.tcc IncludeArithmeticObject.hh OperatorFactory.tcc OperatorFactory.hh SumSimplificationRoutines.cpp SumSimplificationRoutines.hh IncludeEquality.hh)

add_subdirectory(Tests)

target_link_libraries(Functions ${LIB_TO_INCLUDE} ${BO_LIB})

set_target_properties(Functions PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
