project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run FunctionsTests.cpp MultiplicationTests.cpp DivisionTests.cpp ParserTests.cpp ExponentiationOperatorsTests.cpp DivisionOperatorsTests.cpp SumOperatorsTests.cpp MultiplicationOperatorsTests.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run Functions)

target_link_libraries(Google_Tests_run gtest gtest_main)