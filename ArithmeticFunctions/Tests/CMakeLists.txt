project(ArithmeticFunctionsTests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ArithmeticFunctionsTests tests.cpp ../src/ArithmeticFunctions.cpp)
target_link_libraries(ArithmeticFunctionsTests gtest gtest_main)