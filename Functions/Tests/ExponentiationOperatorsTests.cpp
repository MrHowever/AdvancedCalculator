#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

MC::FN::Variable x('x');
MC::FN::Variable y('y');
MC::FN::Variable z('z');
auto square = x ^ 2;

TEST(ExponentiationTestsSuite, ExpVal)
{
    auto result = square ^ 5;
    ASSERT_EQ("x ^ 10", result->print());
}

TEST(ExponentiationTestsSuite, ExpValZero)
{
    auto result = square ^ 0;
    ASSERT_EQ("1", result->print());
}

TEST(ExponentiationTestsSuite, ExpValOne)
{
    auto result = square ^ 1;
    ASSERT_EQ("x ^ 2", result->print());
}

TEST(ExponentiationTestsSuite, ExpValMinusOne)
{
    auto result = square ^ (-1);
    ASSERT_EQ("1 / (x ^ 2)", result->print());
}

TEST(ExponentiationTestsSuite, ExpVar)
{
    auto result = square ^ y;
    ASSERT_EQ("x ^ (2y)", result->print());
}

TEST(ExponentiationTestsSuite, ExpSum)
{
    auto sum = x + 5;
    auto result = square ^ sum;
    ASSERT_EQ("x ^ (2x + 10)", result->print());
}

TEST(ExponentiationTestsSuite, ExpMult)
{
    auto mult = x * y;
    auto result = square ^ mult;
    ASSERT_EQ("x ^ (2xy)", result->print());
}

TEST(ExponentiationTestsSuite, ExpExp)
{
    auto result = square ^ square;
    ASSERT_EQ("x ^ (2(x ^ 2))", result->print());
}

TEST(ExponentiationTestsSuite, ExpDiv)
{
    auto div = y / 2;
    auto result = square ^ div;
    ASSERT_EQ("x ^ y", result->print());
}

TEST(ExponentiationTestsSuite, ZeroVal)
{
    auto result = 0 ^ x;
    ASSERT_EQ("0", result->print());
}

TEST(ExponentiationTestsSuite, OneVal)
{
    auto result = 1 ^ (x + 5);
    ASSERT_EQ("1", result->print());
}

TEST(ExponentiationTestsSuite, ZeroPow)
{
    auto result = square ^ 0;
    ASSERT_EQ("1", result->print());
}

TEST(ExponentiationTestsSuite, OnePow)
{
    auto result = square ^ 1;
    ASSERT_EQ("x ^ 2", result->print());
}

TEST(ExponentiationTestsSuite, OnePow2)
{
    auto result = (x + 1) ^ 1;
    ASSERT_EQ("x + 1", result->print());
}

TEST(ExponentiationTestsSuite, MinusTwoPow)
{
    auto result = square ^ -2;
    ASSERT_EQ("1 / (x ^ 4)", result->print());
}

TEST(ExponentiationTestsSuite, ValExp)
{
    auto result = 5 ^ square;
    ASSERT_EQ("5 ^ (x ^ 2)", result->print());
}

TEST(ExponentiationTestsSuite, ZeroExp)
{
    auto result = 0 ^ square;
    ASSERT_EQ("0", result->print());
}

TEST(ExponentiationTestsSuite, OneExp)
{
    auto result = 1 ^ square;
    ASSERT_EQ("1", result->print());
}

TEST(ExponentiationTestsSuite, ExpZeroPow)
{
    auto result = square ^ 0;
    ASSERT_EQ("1", result->print());
}

TEST(ExponentiationTestsSuite, ExpOnePow)
{
    auto result = square ^ 1;
    ASSERT_EQ("x ^ 2", result->print());
}

TEST(ExponentiationTestsSuite, ExpMinusOnePow)
{
    auto result = square ^ -1;
    ASSERT_EQ("1 / (x ^ 2)", result->print());
}

TEST(ExponentiationTestsSuite, ExpMinusTwoPow)
{
    auto result = square ^ -2;
    ASSERT_EQ("1 / (x ^ 4)", result->print());
}

TEST(ExponentiationTestsSuite, Default)
{
    auto result = (x + 1) ^ (5 * y);
    ASSERT_EQ("(x + 1) ^ (5y)", result->print());
}