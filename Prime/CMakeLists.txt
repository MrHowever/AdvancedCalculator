cmake_minimum_required(VERSION 3.14)
project(Prime)

set(CMAKE_CXX_STANDARD 17)

add_library(Prime Prime.hh Prime.cpp PrimeException.hh)