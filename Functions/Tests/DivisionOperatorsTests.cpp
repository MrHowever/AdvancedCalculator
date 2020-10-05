#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

extern MC::FN::Variable x;
extern MC::FN::Variable y;
extern MC::FN::Variable z;
MC::FN::Variable v('v');

TEST(DivisionTestsSuite, VarVal)
{
    auto result = x / 5;
    ASSERT_EQ("0.2x", result->print());
}

TEST(DivisionTestsSuite, MulVal)
{
    auto result = (5 * y * x) / 5;
    ASSERT_EQ("xy", result->print());
}

TEST(DivisionTestsSuite, SumVal)
{
    auto result = (x + 10) / 5;
    ASSERT_EQ("0.2x + 2", result->print());
}

TEST(DivisionTestsSuite, DivVal)
{
    auto result = (x / y) / 5;
    ASSERT_EQ("0.2x / y", result->print());
}

TEST(DivisionTestsSuite, ExpVal)
{
    auto result = (x ^ 3) / 5;
    ASSERT_EQ("0.2(x ^ 3)", result->print());
}

TEST(DivisionTestsSuite, MulMul)
{
    auto result = (x * y * z) / (x * y);
    ASSERT_EQ("z", result->print());
}

TEST(DivisionTestsSuite, MulMulNotSimp)
{
    auto result = (x * y) / (z * v);
    ASSERT_EQ("xy / vz", result->print());
}

TEST(DivisionTestsSuite, MulSum)
{
    auto result = (x * y * z) / (x + y);
    ASSERT_EQ("xyz / (x + y)", result->print());
}

TEST(DivisionTestsSuite, MulDiv)
{
    auto result = (x * y) / (x / z);
    ASSERT_EQ("yz", result->print());
}

TEST(DivisionTestsSuite, MulExp)
{
    auto result = (x * y) / (x ^ 3);
    ASSERT_EQ("y / (x ^ 2)", result->print());
}

TEST(DivisionTestsSuite, MulVar)
{
    auto result = (x * y) / x;
    ASSERT_EQ("y", result->print());
}

TEST(DivisionTestsSuite, SumMul)
{
    auto result = (x + y) / (x * z);
    ASSERT_EQ("(x + y) / xz", result->print());
}

TEST(DivisionTestsSuite, VarMul)
{
    auto result = x / (x * z);
    ASSERT_EQ("1 / z", result->print());
}

TEST(DivisionTestsSuite, DivisionMul)
{
    auto result = (x / y) / (x * z);
    ASSERT_EQ("1 / yz", result->print());
}

TEST(DivisionTestsSuite, ExpMul)
{
    auto result = (x ^ 3) / (x * z);
    ASSERT_EQ("(x ^ 2) / z", result->print());
}

TEST(DivisionTestsSuite, ExpMul2)
{
    auto result = (x ^ 3) / (y * z * (x ^ 5));
    ASSERT_EQ("1 / (yz(x ^ 2))", result->print());
}

TEST(DivisionTestsSuite, ExpMul3)
{
    auto result = (x ^ 5) / (y * z * (x ^ 3));
    ASSERT_EQ("(x ^ 2) / yz", result->print());
}

TEST(DivisionTestsSuite, ExpMul4)
{
    auto result = (x ^ x) / (y * z * (x ^ y));
    ASSERT_EQ("(x ^ (x + -y)) / yz", result->print());
}

TEST(DivisionTestsSuite, ExpMul5)
{
    auto result = (x ^ (x + 5)) / (y * z * (x ^ (y + -7)));
    ASSERT_EQ("(x ^ (x + -y + 12)) / yz", result->print());
}

TEST(DivisionTestsSuite, ExpMul6)
{
    auto result = x / (y * z * (x ^ (y + -7)));
    ASSERT_EQ("1 / (yz(x ^ (y + -8)))", result->print());
}

TEST(DivisionTestsSuite, ValMul)
{
    auto result = 5 / (x * z);
    ASSERT_EQ("5 / xz", result->print());
}

TEST(DivisionTestsSuite, DivVar)
{
    auto result = (x / y) / z;
    ASSERT_EQ("x / yz", result->print());
}

TEST(DivisionTestsSuite, DivVar2)
{
    auto result = (x / y) / y;
    ASSERT_EQ("x / (y ^ 2)", result->print());
}

TEST(DivisionTestsSuite, DivVal2)
{
    auto result = (x / y) / 5;
    ASSERT_EQ("0.2x / y", result->print());
}

TEST(DivisionTestsSuite, DivSum)
{
    auto result = (x / y) / (z + 1);
    ASSERT_EQ("x / (y + yz)", result->print());
}

TEST(DivisionTestsSuite, DivMul)
{
    auto result = (x / y) / z;
    ASSERT_EQ("x / yz", result->print());
}

TEST(DivisionTestsSuite, DivExp)
{
    auto result = (x / y) / (z ^ 2);
    ASSERT_EQ("x / (y(z ^ 2))", result->print());
}

TEST(DivisionTestsSuite, VarDiv)
{
    auto result = z / (x / y);
    ASSERT_EQ("yz / x", result->print());
}

TEST(DivisionTestsSuite, ValDiv)
{
    auto result = 5 / (x / y);
    ASSERT_EQ("5y / x", result->print());
}

TEST(DivisionTestsSuite, SumDiv)
{
    auto result = (z + 2) / (x / y);
    ASSERT_EQ("(2y + yz) / x", result->print());
}

TEST(DivisionTestsSuite, MulDiv2)
{
    auto result = (z * x) / (x / y);
    ASSERT_EQ("yz", result->print());
}

TEST(DivisionTestsSuite, ExpDiv)
{
    auto result = (x^3) / (x / y);
    ASSERT_EQ("y(x ^ 2)", result->print());
}

TEST(DivisionTestsSuite, DivDiv)
{
    auto result = (z / y) / (x / y);
    ASSERT_EQ("z / x", result->print());
}

TEST(DivisionTestsSuite, DivDiv2)
{
    auto result = (x / y) / (x / y);
    ASSERT_EQ("1", result->print());
}

TEST(DivisionTestsSuite, Default)
{
    auto result = (x + y) / (z ^ v);
    ASSERT_EQ("(x + y) / (z ^ v)", result->print());
}