cmake_minimum_required(VERSION 3.14)
project(SpecialNumbers)

set(CMAKE_CXX_STANDARD 17)

add_library(SpecialNumbers FermatNumber.hh FermatNumber.cpp MersenneNumber.hh MersenneNumber.cpp InvalidParameterException.hh)