cmake_minimum_required(VERSION 3.14)
project(Random)

set(CMAKE_CXX_STANDARD 17)

add_library(Random Random.hh Random.cpp Randomizable.hh RandomizerException.hh)