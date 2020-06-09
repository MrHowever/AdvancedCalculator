cmake_minimum_required(VERSION 3.14)
project(BasicOperations)

set(CMAKE_CXX_STANDARD 17)

find_library(LIB_TO_INCLUDE TypeTraits /home/mrhowever/Programming/Projects/TypeTraits/lib)
find_library(INTERFACES_LIB Interfaces /home/mrhowever/Programming/Projects/Interfaces/lib)
include_directories(/home/mrhowever/Programming/Projects/TypeTraits/include /home/mrhowever/Programming/Projects/Interfaces/include)

add_library(BasicOperations include/BasicOperations.hh include/BasicOperationsException.hh src/BasicOperations.cpp)

set_target_properties(BasicOperations PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

target_link_libraries(BasicOperations ${LIB_TO_INCLUDE} ${INTERFACES_LIB})

set_target_properties(BasicOperations PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
