cmake_minimum_required(VERSION 3.14)
project(ModularOperations)

set(CMAKE_CXX_STANDARD 17)

add_library(ModularOperations ModularOperations.hh ModularOperations.cpp)
link_directories(~/Programming/Projects/BasicOperations)
target_link_libraries(ModularOperations LINK_PUBLIC BasicOperations)