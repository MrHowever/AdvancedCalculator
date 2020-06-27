//
// Created by mrhowever on 03.03.2020.
//

#include "gtest/gtest.h"
#include "../Sum.hh"
#include "../Division.hh"
#include "../Multiplication.hh"
#include "../Value.hh"
#include "../Variable.hh"
#include "../Logarithm.hh"

TEST(ConversionTestSuite, VarValDiv)
{
    MC::FN::Variable var('x');
    auto result = var / 5;
    ASSERT_EQ("x / 5", result.print());
}

TEST(ConversionTestSuite, ValVarDiv)
{
    MC::FN::Variable var('x');
    auto result = 5 / var;
    ASSERT_EQ("5 / x", result.print());
}

TEST(ConversionTestSuite, VarVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var / var2;
    ASSERT_EQ("x / y", result.print());
}

TEST(ConversionTestSuite, DivValDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Division div(var / 5);
    auto result = div / 6;
    ASSERT_EQ("x / (30)", result.print());
}

TEST(ConversionTestSuite, ValDivDiv)
{
    MC::FN::Variable var('x');
    auto result = 6 / (5 / var);
    ASSERT_EQ("(6x) / 5", result.print());
}

TEST(ConversionTestSuite, DivVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var / 5) / var2;
    ASSERT_EQ("x / (5y)", result.print());
}

TEST(ConversionTestSuite, VarDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var / (5 / var2);
    ASSERT_EQ("(xy) / 5", result.print());
}

TEST(ConversionTestSuite, DivDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var / 6) / (5 / var2);
    ASSERT_EQ("(yx) / (30)", result.print());
}

TEST(ConversionTestSuite, VarSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = var / sum;
    ASSERT_EQ("x / (y + 5)", result.print());
}

TEST(ConversionTestSuite, SumVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = sum / var;
    ASSERT_EQ("(y + 5) / x", result.print());
}

TEST(ConversionTestSuite, ValSumDiv)
{
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = 5 / sum;
    ASSERT_EQ("5 / (y + 5)", result.print());
}

TEST(ConversionTestSuite, SumValDiv)
{
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = sum / 5;
    ASSERT_EQ("(y + 5) / 5", result.print());
}

TEST(ConversionTestSuite, SumSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Sum sum2 = var2 + 7;
    auto result = sum / sum2;
    ASSERT_EQ("(x + 5) / (y + 7)", result.print());
}

TEST(ConversionTestSuite, MultSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = mult / sum;
    ASSERT_EQ("(5x) / (y + 7)", result.print());
}

TEST(ConversionTestSuite, SumMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = sum / mult;
    ASSERT_EQ("(y + 7) / (5x)", result.print());
}

TEST(ConversionTestSuite, SumDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Division div = var2 / 7;
    auto result = sum / div;
    ASSERT_EQ("((x + 5) * 7) / y", result.print());
}

TEST(ConversionTestSuite, DivSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Division div = var2 / 7;
    auto result = div / sum;
    ASSERT_EQ("y / ((x + 5) * 7)", result.print());
}

TEST(ConversionTestSuite, VarMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var2 * 5;
    auto result = var / mult;
    ASSERT_EQ("x / (5y)", result.print());
}

TEST(ConversionTestSuite, MultVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var2 * 5;
    auto result = mult / var;
    ASSERT_EQ("(5y) / x", result.print());
}

TEST(ConversionTestSuite, ValMultDiv)
{
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var2 * 5;
    auto result = 5 / mult;
    ASSERT_EQ("1 / (y)", result.print());
}

TEST(ConversionTestSuite, MultValDiv)
{
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var2 * 5;
    auto result = mult / 5;
    ASSERT_EQ("(y) / 1 jaktoskrocic", result.print());
}

TEST(ConversionTestSuite, MultMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Variable mult = var * 5;
    MC::FN::Variable mult2 = var2 * 7;
    auto result = mult / mult2;
    ASSERT_EQ("(5x) / (7y)", result.print());
}

TEST(ConversionTestSuite, DivMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Variable mult = var2 * 7;
    auto result = div / mult;
    ASSERT_EQ("x / (35y)", result.print());
}

TEST(ConversionTestSuite, MultDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Variable mult = var2 * 7;
    auto result = mult / div;
    ASSERT_EQ("(35y) / x", result.print());
}