//
// Created by mrhowever on 20.10.19.
//

#include "gtest/gtest.h"
#include "../IncludeSum.hh"
#include "../IncludeValue.hh"
#include "../Variable.hh"
#include "../IncludeDivision.hh"
#include "../Multiplication.hh"
#include "../Logarithm.hh"
#include "../LogarithmMap.hh"

#include <chrono>
#include <random>

TEST(ConversionTestSuite, VarValMult)
{
    MC::FN::Variable var('x');
    auto result = var * 5;
    ASSERT_EQ("5x", result.print());
}

TEST(ConversionTestSuite, ValVarMult)
{
    MC::FN::Variable var('x');
    auto result = 5 * var;
    ASSERT_EQ("5x", result.print());
}

TEST(ConversionTestSuite, VarVarMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var * var2;
    ASSERT_EQ("yx", result.print());
}

TEST(ConversionTestSuite, MultValMult)
{
    MC::FN::Variable var('x');
    auto result = (var * 5) * 6;
    ASSERT_EQ("30x", result.print());
}

TEST(ConversionTestSuite, ValMultMult)
{
    MC::FN::Variable var('x');
    auto result = 6 * (5 * var);
    ASSERT_EQ("30x", result.print());
}

TEST(ConversionTestSuite, MultVarMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var * 5) * var2;
    ASSERT_EQ("5yx", result.print());
}

TEST(ConversionTestSuite, VarMultMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = var * (5 * var2);
    ASSERT_EQ("5yx", result.print());
}

TEST(ConversionTestSuite, MultMultMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    auto result = (var * 6) * (5 * var2);
    ASSERT_EQ("30yx", result.print());
}

TEST(ConversionTestSuite, VarSumMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = var * sum;
    ASSERT_EQ("x * (y + 5)", result.print());
}

TEST(ConversionTestSuite, SumVarMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = sum * var;
    ASSERT_EQ("x * (y + 5)", result.print());
}

TEST(ConversionTestSuite, ValSumMult)
{
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = 5 * sum;
    ASSERT_EQ("(y + 5) * 5", result.print());
}

TEST(ConversionTestSuite, SumValMult)
{
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var2 + 5;
    auto result = sum * 5;
    ASSERT_EQ("(y + 5) * 5", result.print());
}

TEST(ConversionTestSuite, SumSumMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Sum sum2 = var2 + 7;
    auto result = sum * sum2;
    ASSERT_EQ("(35 + yx + 5y + 7x)", result.print());
}

TEST(ConversionTestSuite, MultSumMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Multiplication mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = mult * sum;
    ASSERT_EQ("x * (y + 7) * 5", result.print());
}

TEST(ConversionTestSuite, SumMultMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Multiplication mult = var * 5;
    MC::FN::Sum sum = var2 + 7;
    auto result = sum * mult;
    ASSERT_EQ("x * (y + 7) * 5", result.print());
}

TEST(ConversionTestSuite, SumDivMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Division div = var2 / 7;
    auto result = sum * div;
    ASSERT_EQ("(x + 5) * (y / 7)", result.print());
}

TEST(ConversionTestSuite, DivSumMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Sum sum = var + 5;
    MC::FN::Division div = var2 / 7;
    auto result = div * sum;
    ASSERT_EQ("(x + 5) * (y / 7)", result.print());
}

TEST(ConversionTestSuite, VarDivMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = var * div;
    ASSERT_EQ("x * (y / 5)", result.print());
}

TEST(ConversionTestSuite, DivVarMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = div * var;
    ASSERT_EQ("x * (y / 5)", result.print());
}

TEST(ConversionTestSuite, ValDivMult)
{
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = 5 * div;
    ASSERT_EQ("(y / 5) * 5", result.print());
}

TEST(ConversionTestSuite, DivValMult)
{
    MC::FN::Variable var2('y');
    MC::FN::Division div = var2 / 5;
    auto result = div * 5;
    ASSERT_EQ("(y / 5) * 5", result.print());
}

TEST(ConversionTestSuite, DivDivMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Division div2 = var2 / 7;
    auto result = div * div2;
    ASSERT_EQ("(yx) / (35)", result.print());
}

TEST(ConversionTestSuite, DivMultMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Multiplication mult = var2 * 7;
    auto result = div * mult;
    ASSERT_EQ("y * (x / 5) * 7", result.print());
}

TEST(ConversionTestSuite, MultDivMult)
{
    MC::FN::Variable var('x');
    MC::FN::Variable var2('y');
    MC::FN::Division div = var / 5;
    MC::FN::Multiplication mult = var2 * 7;
    auto result = mult * div;
    ASSERT_EQ("y * (x / 5) * 7", result.print());
}