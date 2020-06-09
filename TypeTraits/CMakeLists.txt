cmake_minimum_required(VERSION 3.14)
project(TypeTraits)

set(CMAKE_CXX_STANDARD 17)

add_library(TypeTraits include/CustomTypeTraits.hh src/CustomTypeTraits.cpp)

set_target_properties(TypeTraits PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
