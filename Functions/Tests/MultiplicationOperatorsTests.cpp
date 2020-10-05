#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

extern MC::FN::Variable x;
extern MC::FN::Variable y;
extern MC::FN::Variable z;
extern MC::FN::Variable v;

TEST(MultiplicationTestsSuite, DivVar)
{
    auto result = (x / z) * y;
    ASSERT_EQ("xy / z", result->print());
}

TEST(MultiplicationTestsSuite, DivVal)
{
    auto result = (x / z) * 5;
    ASSERT_EQ("5x / z", result->print());
}

TEST(MultiplicationTestsSuite, DivExp)
{
    auto result = (x / z) * (x ^ 3);
    ASSERT_EQ("(x ^ 4) / z", result->print());
}

TEST(MultiplicationTestsSuite, DivExp2)
{
    auto result = (x / z) * (y ^ 2);
    ASSERT_EQ("(x(y ^ 2)) / z", result->print());
}

TEST(MultiplicationTestsSuite, DivDiv)
{
    auto result = (x / z) * (y / z);
    ASSERT_EQ("xy / (z ^ 2)", result->print());
}

TEST(MultiplicationTestsSuite, DivSum)
{
    auto result = (x / z) * (y + x);
    ASSERT_EQ("(x ^ 2 + xy) / z", result->print());
}

TEST(MultiplicationTestsSuite, DivMul)
{
    auto result = (x / z) * (y * x);
    ASSERT_EQ("(y(x ^ 2)) / z", result->print());
}

TEST(MultiplicationTestsSuite, ValZero)
{
    auto result = 0 * (x + 1);
    ASSERT_EQ("0", result->print());
}

TEST(MultiplicationTestsSuite, ValOne)
{
    auto result = 1 * (x / z);
    ASSERT_EQ("x / z", result->print());
}

TEST(MultiplicationTestsSuite, ValVar)
{
    auto result = 5 * x;
    ASSERT_EQ("5x", result->print());
}

TEST(MultiplicationTestsSuite, ValSum)
{
    auto result = 5 * (x + z + 6);
    ASSERT_EQ("5x + 5z + 30", result->print());
}

TEST(MultiplicationTestsSuite, ValMult)
{
    auto result = 5 * x * (y + 1);
    ASSERT_EQ("5x + 5xy", result->print());
}

TEST(MultiplicationTestsSuite, ValExp)
{
    auto result = 5 * (x ^ z);
    ASSERT_EQ("5(x ^ z)", result->print());
}

TEST(MultiplicationTestsSuite, ValDiv)
{
    auto result = 5 * (x / z);
    ASSERT_EQ("5x / z", result->print());
}

TEST(MultiplicationTestsSuite, ExpVal)
{
    auto result = (x ^ z) * 5;
    ASSERT_EQ("5(x ^ z)", result->print());
}

TEST(MultiplicationTestsSuite, ExpVar)
{
    auto result = (x ^ z) * x;
    ASSERT_EQ("x ^ (z + 1)", result->print());
}

TEST(MultiplicationTestsSuite, ExpVar2)
{
    auto result = (x ^ z) * y;
    ASSERT_EQ("y(x ^ z)", result->print());
}

TEST(MultiplicationTestsSuite, ExpExp)
{
    auto result = (x ^ z) * (x ^ y);
    ASSERT_EQ("x ^ (y + z)", result->print());
}

TEST(MultiplicationTestsSuite, ExpExp2)
{
    auto result = (x ^ z) * (z ^ y);
    ASSERT_EQ("(x ^ z)(z ^ y)", result->print());
}

TEST(MultiplicationTestsSuite, ExpSum)
{
    auto result = (x ^ z) * (x + 5);
    ASSERT_EQ("x ^ (z + 1) + 5(x ^ z)", result->print());
}

TEST(MultiplicationTestsSuite, ExpMul)
{
    auto result = (x ^ z) * (x * y);
    ASSERT_EQ("y(x ^ (z + 1))", result->print());
}

TEST(MultiplicationTestsSuite, ExpDiv)
{
    auto result = (x ^ z) * (x / y);
    ASSERT_EQ("(x ^ (z + 1)) / y", result->print());
}

TEST(MultiplicationTestsSuite, SumMulSplit)
{
    auto result = (x + z + 5) * (x * y * z * v * 6);
    ASSERT_EQ("6vxy(z ^ 2) + 30vxyz + 6vyz(x ^ 2)", result->print());
}

TEST(MultiplicationTestsSuite, MulMul)
{
    auto result = (x * z * 5) * (x * y * z * v * 6);
    ASSERT_EQ("30vy(x ^ 2)(z ^ 2)", result->print());
}

TEST(MultiplicationTestsSuite, SumSum)
{
    auto result = (x + z + 5) * (y + x + 2);
    ASSERT_EQ("7x + 5y + 2z + x ^ 2 + xz + yz + xy + 10", result->print());
}

TEST(MultiplicationTestsSuite, SumMul)
{
    auto result = (x + z + 5) * (y * x * 2);
    ASSERT_EQ("10xy + 2y(x ^ 2) + 2xyz", result->print());
}

TEST(MultiplicationTestsSuite, MulSum)
{
    auto result = (y * x * 2) * (x + z + 5);
    ASSERT_EQ("10xy + 2y(x ^ 2) + 2xyz", result->print());
}

TEST(MultiplicationTestsSuite, Default)
{
    auto result = x * y * (z ^ 2);
    ASSERT_EQ("xy(z ^ 2)", result->print());
}