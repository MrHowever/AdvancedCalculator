cmake_minimum_required(VERSION 3.14)
project(PrimitiveRoots)

set(CMAKE_CXX_STANDARD 17)

add_library(PrimitiveRoots library.cpp library.h PrimitiveRootException.hh)