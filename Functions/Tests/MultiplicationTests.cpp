#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

/*
 *
 *              VALUE * VALUE TESTS
 *
 */

TEST(ConversionTestSuite, VarValMult)
{
    MC::FN::Variable x('x');
    auto result = x * 5;
    ASSERT_EQ("5x", result->print());
}

TEST(ConversionTestSuite, ValVarMult)
{
    MC::FN::Variable x('x');
    auto result = 5 * x;
    ASSERT_EQ("5x", result->print());
}

TEST(ConversionTestSuite, VarVarMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = x * y;
    ASSERT_EQ("xy", result->print());
}

TEST(ConversionTestSuite, SameVarVarMult)
{
    MC::FN::Variable x('x');
    auto result = x * x * x;
    ASSERT_EQ("x ^ 3", result->print());
}

TEST(ConversionTestSuite, ValPrimMult)
{
    MC::FN::Value val(5);
    auto result = val * 5;
    ASSERT_EQ("25", result->print());
}

TEST(ConversionTestSuite, PrimValMult)
{
    MC::FN::Value val(5);
    auto result = 5 * val;
    ASSERT_EQ("25", result.print());
}

TEST(ConversionTestSuite, SameValValMult)
{
    MC::FN::Value val(5);
    auto result = val * val;
    ASSERT_EQ("25", result.print());
}

/*
 *
 *                  COMPLEX * VALUE TESTS
 *
 */

TEST(ConversionTestSuite, MultValMult)
{
    MC::FN::Variable x('x');
    auto result = (x * 5) * 6;
    ASSERT_EQ("30x", result->print());
}

TEST(ConversionTestSuite, ValMultMult)
{
    MC::FN::Variable x('x');
    auto result = 6 * (5 * x);
    ASSERT_EQ("30x", result->print());
}

TEST(ConversionTestSuite, MultVarMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = (x * 5) * y;
    ASSERT_EQ("5xy", result->print());
}

TEST(ConversionTestSuite, VarMultMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = x * (5 * y);
    ASSERT_EQ("5xy", result->print());
}

TEST(ConversionTestSuite, VarSumMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto sum = y + 5;
    auto result = sum * x;
    ASSERT_EQ("5x + xy", result->print());
}

TEST(ConversionTestSuite, SumVarMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto sum = y + 5;
    auto result = sum * x;
    ASSERT_EQ("5x + xy", result->print());
}

TEST(ConversionTestSuite, ValSumMult)
{
    MC::FN::Variable y('y');
    auto sum = y + 5;
    auto result = MC::FN::Value(5) * sum;
    ASSERT_EQ("5y + 25", result->print());
}

TEST(ConversionTestSuite, SumValMult)
{
    MC::FN::Variable y('y');
    auto sum = y + 5;
    auto result = sum * 5;
    ASSERT_EQ("5y + 25", result->print());
}

TEST(ConversionTestSuite, VarDivMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto div = y / 5;
    auto result = x * div;
    ASSERT_EQ("0.2xy", result->print());
}

TEST(ConversionTestSuite, DivVarMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto div = y / 5;
    auto result = div * x;
    ASSERT_EQ("0.2xy", result->print());
}

TEST(ConversionTestSuite, ValDivMult)
{
    MC::FN::Variable y('y');
    auto div = y / 5;
    auto result = 5 * div;
    ASSERT_EQ("y", result->print());
}

TEST(ConversionTestSuite, DivValMult)
{
    MC::FN::Variable y('y');
    auto div = y / 5;
    auto result = div * 5;
    ASSERT_EQ("y", result->print());
}

/*
 *
 *              COMPLEX * COMPLEX TESTS
 *
 */

TEST(ConversionTestSuite, MultMultMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = (x * 6) * (5 * y);
    ASSERT_EQ("30xy", result->print());
}

TEST(ConversionTestSuite, SumSumMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto sum = x + 5;
    auto sum2 = y + 7;
    auto result = sum * sum2;
    ASSERT_EQ("7x + 5y + xy + 35", result->print());
}

TEST(ConversionTestSuite, MultSumMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto mult = x * 5;
    auto sum = y + 7;
    auto result = mult * sum;
    ASSERT_EQ("35x + 5xy", result->print());
}

TEST(ConversionTestSuite, SumMultMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto mult = x * 5;
    auto sum = y + 7;
    auto result = sum * mult;
    ASSERT_EQ("35x + 5xy", result->print());
}

TEST(ConversionTestSuite, SumDivMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto sum = x + 5;
    auto div = y / 7;
    auto result = sum * div;
    ASSERT_EQ("0.714286y + 0.142857xy", result->print());
}

TEST(ConversionTestSuite, DivSumMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto sum = x + 5;
    auto div = y / 7;
    auto result = div * sum;
    ASSERT_EQ("0.714286y + 0.142857xy", result->print());
}

TEST(ConversionTestSuite, DivDivMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto div = x / 5;
    auto div2 = y / 7;
    auto result = div * div2;
    ASSERT_EQ("0.0285714xy", result->print());
}

TEST(ConversionTestSuite, DivMultMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto div = x / 5;
    auto mult = y * 7;
    auto result = div * mult;
    ASSERT_EQ("1.4xy", result->print());
}

TEST(ConversionTestSuite, MultDivMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto div = x / 5;
    auto mult = y * 7;
    auto result = mult * div;
    ASSERT_EQ("1.4xy", result->print());
}

/*
 *
 *                  SIMPLIFICATIONS
 *
 *
 */

TEST(ConversionTestSuite, ExpSimplificationMult)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = x * y * (x ^ 4);
    ASSERT_EQ("y(x ^ 5)", result->print());
}