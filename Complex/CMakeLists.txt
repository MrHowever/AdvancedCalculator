cmake_minimum_required(VERSION 3.14)
project(Complex)

set(CMAKE_CXX_STANDARD 17)


find_library(LIB_TO_INCLUDE ArithmeticFunctions /home/mrhowever/Programming/Projects/ArithmeticFunctions/lib)
include_directories(/home/mrhowever/Programming/Projects/ArithmeticFunctions/include)
include_directories(/home/mrhowever/Programming/Projects/ConstantVariables/include)

add_library(Complex include/Complex.hh src/Complex.cpp)

#add_subdirectory(Tests)
target_link_libraries(Complex ${LIB_TO_INCLUDE})

set_target_properties(Complex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)