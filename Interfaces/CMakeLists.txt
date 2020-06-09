cmake_minimum_required(VERSION 3.14)
project(Interfaces)

set(CMAKE_CXX_STANDARD 17)

add_library(Interfaces include/BitShiftable.hh src/BitShiftable.cpp include/Bounded.hh src/Bounded.cpp include/Comparable.hh src/Comparable.cpp include/EqualityComparable.hh)

set_target_properties(Interfaces PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)