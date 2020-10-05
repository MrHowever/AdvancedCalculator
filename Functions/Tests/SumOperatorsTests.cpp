#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

extern MC::FN::Variable x;
extern MC::FN::Variable y;
extern MC::FN::Variable z;
extern MC::FN::Variable v;

TEST(SumTestsSuite, DivVar)
{
    auto result = (x / z) + y;
    ASSERT_EQ("(x + yz) / z", result->print());
}

TEST(SumTestsSuite, DivVal)
{
    auto result = (x / z) + 5;
    ASSERT_EQ("(x + 5z) / z", result->print());
}

TEST(SumTestsSuite, DivExp)
{
    auto result = (x / z) + (y ^ 2);
    ASSERT_EQ("(x + z(y ^ 2)) / z", result->print());
}

TEST(SumTestsSuite, DivSum)
{
    auto result = (x / z) + (y + v);
    ASSERT_EQ("(x + vz + yz) / z", result->print());
}

TEST(SumTestsSuite, DivMult)
{
    auto result = (x / z) + (y * 5);
    ASSERT_EQ("(x + 5yz) / z", result->print());
}

TEST(SumTestsSuite, DivDiv)
{
    auto result = (x / z) + (y / v);
    ASSERT_EQ("(vx + yz) / vz", result->print());
}

TEST(SumTestsSuite, MulVar)
{
    auto result = (x * y) + z;
    ASSERT_EQ("z + xy", result->print());
}

TEST(SumTestsSuite, MulVar2)
{
    auto result = (x * y) + x;
    ASSERT_EQ("x + xy", result->print());
}

TEST(SumTestsSuite, MulVal)
{
    auto result = (x * y) + 5;
    ASSERT_EQ("xy + 5", result->print());
}

TEST(SumTestsSuite, MulMul)
{
    auto result = (x * y) + (x * z);
    ASSERT_EQ("xz + xy", result->print());
}

TEST(SumTestsSuite, MulSum)
{
    auto result = (x * y) + (x + 1);
    ASSERT_EQ("x + xy + 1", result->print());
}

TEST(SumTestsSuite, MulDiv)
{
    auto result = (x * y) + (x / v);
    ASSERT_EQ("(x + vxy) / v", result->print());
}

TEST(SumTestsSuite, SumVar)
{
    auto result = (x + y) + x;
    ASSERT_EQ("2x + y", result->print());
}

TEST(SumTestsSuite, SumVal)
{
    auto result = (x + y) + 5;
    ASSERT_EQ("x + y + 5", result->print());
}

TEST(SumTestsSuite, SumSum)
{
    auto result = (x + y) + (x + z + 5);
    ASSERT_EQ("2x + y + z + 5", result->print());
}

TEST(SumTestsSuite, SumMul)
{
    auto result = (x + y) + (x * z);
    ASSERT_EQ("x + y + xz", result->print());
}

TEST(SumTestsSuite, SumDiv)
{
    auto result = (x + y) + ((x + 5)/ z);
    ASSERT_EQ("(x + xz + yz + 5) / z", result->print());
}

TEST(SumTestsSuite, Default)
{
    auto result = x + x;
    ASSERT_EQ("2x", result->print());
}

TEST(SumTestsSuite, Default2)
{
    auto result = x + y;
    ASSERT_EQ("x + y", result->print());
}