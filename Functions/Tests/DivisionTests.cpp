//
// Created by mrhowever on 03.03.2020.
//

#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"
/*
 *
 *              VALUE / VALUE TESTS
 *
 */

TEST(ConversionTestSuite, VarValDiv)
{
    MC::FN::Variable var('x');
    auto result = var / 5;
    ASSERT_EQ("0.2x", result->print());
}

TEST(ConversionTestSuite, ValVarDiv)
{
    MC::FN::Variable var('x');
    auto result = 5 / var;
    ASSERT_EQ("5 / x", result->print());
}

TEST(ConversionTestSuite, VarVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var / var2;
    ASSERT_EQ("x / y", result->print());
}

TEST(ConversionTestSuite, SameVarVarDiv)
{
    MC::FN::Variable var('x');
    auto result = (var / var) / var;
    ASSERT_EQ("1 / x", result->print());
}

TEST(ConversionTestSuite, SameVarVarDivTwo)
{
    MC::FN::Variable var('x');
    auto result = var / (var / var);
    ASSERT_EQ("x", result->print());
}

TEST(ConversionTestSuite, ValPrimDiv)
{
    MC::FN::Value val(5);
    auto result = val / 5;
    ASSERT_EQ("1", result->print());
}

TEST(ConversionTestSuite, PrimValDiv)
{
    MC::FN::Value val(5);
    auto result = 5 / val;
    ASSERT_EQ("1", result.print());
}

TEST(ConversionTestSuite, SameValValDiv)
{
    MC::FN::Value val(5);
    auto result = val / val;
    ASSERT_EQ("1", result.print());
}

/*
 *
 *                  COMPLEX / VALUE TESTS
 *
 */

TEST(ConversionTestSuite, DivValDiv)
{
    MC::FN::Variable var('x');
    auto div = var / 5;
    auto result = div / 6;
    ASSERT_EQ("0.0333333x", result->print());
}

TEST(ConversionTestSuite, ValDivDiv)
{
    MC::FN::Variable var('x');
    auto result = 6 / (5 / var);
    ASSERT_EQ("1.2x", result->print());
}

TEST(ConversionTestSuite, DivVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var / 5) / var2;
    ASSERT_EQ("0.2x / y", result->print());
}

TEST(ConversionTestSuite, VarDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var / (5 / var2);
    ASSERT_EQ("0.2xy", result->print());
}

TEST(ConversionTestSuite, VarSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto sum = var2 + 5;
    auto result = var / sum;
    ASSERT_EQ("x / (y + 5)", result->print());
}

TEST(ConversionTestSuite, SumVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto sum = var2 + 5;
    auto result = sum / var;
    ASSERT_EQ("(y + 5) / x", result->print());
}

TEST(ConversionTestSuite, ValSumDiv)
{
    MC::FN::Variable var2('y');
    auto sum = var2 + 5;
    auto result = 5 / sum;
    ASSERT_EQ("5 / (y + 5)", result->print());
}

TEST(ConversionTestSuite, SumValDiv)
{
    MC::FN::Variable var2('y');
    auto sum = var2 + 5;
    auto result = sum / 5;
    ASSERT_EQ("0.2y + 1", result->print());
}

TEST(ConversionTestSuite, VarMultDiv)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto mult = y * 5;
    auto result = x / mult;
    ASSERT_EQ("x / 5y", result->print());
}

TEST(ConversionTestSuite, MultVarDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = mult / var;
    ASSERT_EQ("5y / x", result->print());
}

TEST(ConversionTestSuite, ValMultDiv)
{
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = 5 / mult;
    ASSERT_EQ("1 / y", result->print());
}

TEST(ConversionTestSuite, MultValDiv)
{
    MC::FN::Variable var2('y');
    auto mult = var2 * 5;
    auto result = mult / 5;
    ASSERT_EQ("y", result->print());
}

/*
 *
 *          COMPLES / COMPLEX TESTS
 *
 */

TEST(ConversionTestSuite, DivDivDiv)
{
    MC::FN::Variable x('x');
    MC::FN::Variable y('y');
    auto result = (x / 6) / (5 / y);
    ASSERT_EQ("0.0333333xy", result->print());
}

TEST(ConversionTestSuite, SumSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto sum = var + 5;
    auto sum2 = var2 + 7;
    auto result = sum / sum2;
    ASSERT_EQ("(x + 5) / (y + 7)", result->print());
}

TEST(ConversionTestSuite, MultSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    auto sum = var2 + 7;
    auto result = mult / sum;
    ASSERT_EQ("5x / (y + 7)", result->print());
}

TEST(ConversionTestSuite, SumMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    auto sum = var2 + 7;
    auto result = sum / mult;
    ASSERT_EQ("(y + 7) / 5x", result->print());
}

TEST(ConversionTestSuite, SumDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto sum = var + 5;
    auto div = var2 / 7;
    auto result = sum / div;
    ASSERT_EQ("(x + 5) / 0.142857y", result->print());
}

TEST(ConversionTestSuite, DivSumDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto sum = var + 5;
    auto div = var2 / 7;
    auto result = div / sum;
    ASSERT_EQ("0.142857y / (x + 5)", result->print());
}

TEST(ConversionTestSuite, MultMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto mult = var * 5;
    auto mult2 = var2 * 7;
    auto result = mult / mult2;
    ASSERT_EQ("x / 1.4y", result->print());
}

TEST(ConversionTestSuite, DivMultDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto div = var / 5;
    auto mult = var2 * 7;
    auto result = div / mult;
    ASSERT_EQ("x / 35y", result->print());
}

TEST(ConversionTestSuite, MultDivDiv)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto div = var / 5;
    auto mult = var2 * 7;
    auto result = mult / div;
    ASSERT_EQ("35y / x", result->print());
}