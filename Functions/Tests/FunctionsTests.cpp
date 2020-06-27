#include "gtest/gtest.h"
#include "../Sum.hh"
#include "../Division.hh"
#include "../Multiplication.hh"
#include "../Value.hh"
#include "../Variable.hh"


TEST(ConversionTestSuite, VarValSum)
{
    MC::FN::Variable var('x');
    auto result = var + 5;
    ASSERT_EQ("x + 5", result.print());
}

TEST(ConversionTestSuite, ValVarSum)
{
    MC::FN::Variable var('x');
    auto result = 5 + var;
    ASSERT_EQ("x + 5", result.print());
}

TEST(ConversionTestSuite, VarVarSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var + var2;
    ASSERT_EQ("x + y", result.print());
}

//TODO test every structure
TEST(ConversionTestSuite, SameVarVarSum)
{
    MC::FN::Variable var('x');
    auto result = var + var + var;
    ASSERT_EQ("3x", result.print());
}

TEST(ConversionTestSuite, SumValSum)
{
    MC::FN::Variable var('x');
    auto result = (var + 5) + 6;
    ASSERT_EQ("x + 11", result.print());
}

TEST(ConversionTestSuite, ValSumSum)
{
    MC::FN::Variable var('x');
    auto result = 6 + (5 + var);
    ASSERT_EQ("x + 11", result.print());
}

TEST(ConversionTestSuite, SumVarSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var + 5) + var2;
    ASSERT_EQ("x + 5 + y", result.print());
}

TEST(ConversionTestSuite, VarSumSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var + (5 + var2);
    ASSERT_EQ("x + y + 5", result.print());
}

TEST(ConversionTestSuite, SumSumSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var + 6) + (5 + var2);
    ASSERT_EQ("x + 11 + y", result.print());
}

TEST(ConversionTestSuite, VarMultSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = var + mult;
    ASSERT_EQ("x + 5y", result.print());
}

TEST(ConversionTestSuite, MultVarSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = mult + var;
    ASSERT_EQ("5y + x", result.print());
}

TEST(ConversionTestSuite, ValMultSum)
{
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = 5 + mult;
    ASSERT_EQ("5y + 5", result.print());
}

TEST(ConversionTestSuite, MultValSum)
{
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = mult + 5;
    ASSERT_EQ("5y + 5", result.print());
}

TEST(ConversionTestSuite, MultMultSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    auto mult2 = var2 * 7;
    auto result = mult + mult2;
    ASSERT_EQ("5x + 7y", result.print());
}

TEST(ConversionTestSuite, MultSumSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = mult + sum;
    ASSERT_EQ("5x + y + 7", result.print());
}

TEST(ConversionTestSuite, SumMultSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = sum + mult;
    ASSERT_EQ("y + 7 + 5x", result.print());
}

TEST(ConversionTestSuite, MultDivSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    MC::FN::Division div = var2 / 7;
    auto result = mult + div;
    ASSERT_EQ("5x + y / 7", result.print());
}

TEST(ConversionTestSuite, DivMultSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    MC::FN::Division div = var2 / 7;
    auto result = div + mult;
    ASSERT_EQ("y / 7 + 5x", result.print());
}

TEST(ConversionTestSuite, VarDivSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = var + div;
    ASSERT_EQ("x + y / 5", result.print());
}

TEST(ConversionTestSuite, DivVarSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = div + var;
    ASSERT_EQ("y / 5 + x", result.print());
}

TEST(ConversionTestSuite, ValDivSum)
{
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = 5 + div;
    ASSERT_EQ("y / 5 + 5", result.print());
}

TEST(ConversionTestSuite, DivValSum)
{
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = div + 5;
    ASSERT_EQ("y / 5 + 5", result.print());
}

TEST(ConversionTestSuite, DivDivSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Division div2 = var2 / 7;
    auto result = div + div2;
    ASSERT_EQ("(7x + 5y) / (35)", result.print());
}

TEST(ConversionTestSuite, DivSumSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = div + sum;
    ASSERT_EQ("x / 5 + y + 7", result.print());
}

TEST(ConversionTestSuite, SumDivSum)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = sum + div;
    ASSERT_EQ("y + 7 + x / 5", result.print());
}