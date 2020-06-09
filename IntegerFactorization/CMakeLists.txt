cmake_minimum_required(VERSION 3.14)
project(IntegerFactorization)

set(CMAKE_CXX_STANDARD 17)

add_library(IntegerFactorization PrimeFactorization.hh PrimeFactorization.cpp)