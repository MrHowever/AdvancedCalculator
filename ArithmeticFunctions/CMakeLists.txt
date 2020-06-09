cmake_minimum_required(VERSION 3.14)
project(ArithmeticFunctions)

set(CMAKE_CXX_STANDARD 17)

find_library(LIB_TO_INCLUDE Interfaces /home/mrhowever/Programming/Projects/Interfaces/lib)
include_directories(/home/mrhowever/Programming/Projects/Interfaces/include)

add_library(ArithmeticFunctions include/ArithmeticFunctions.hh src/ArithmeticFunctions.cpp include/ArithmeticFunctionException.hh src/Logarithm.cpp include/Logarithm.hh)
add_subdirectory(Tests)
target_link_libraries(ArithmeticFunctions ${LIB_TO_INCLUDE})

set_target_properties(ArithmeticFunctions PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
