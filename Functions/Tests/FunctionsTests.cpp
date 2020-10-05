#include "gtest/gtest.h"
#include "../MultiplicationOperators.hh"
#include "../DivisionOperators.hh"
#include "../AdditionOperators.hh"
#include "../ExponentiationOperators.hh"

namespace MC::FN
{

/*
 *
 *                  VALUE TESTS
 *
 *
 */


    TEST(SumTestSuite, VarValSum)
    {
        MC::FN::Variable var('x');
        auto result = var + 5;
        ASSERT_EQ("x + 5", result->print());
    }

    TEST(SumTestSuite, ValVarSum)
    {
        MC::FN::Variable var('x');
        auto result = 5 + var;
        ASSERT_EQ("x + 5", result->print());
    }

    TEST(SumTestSuite, VarVarSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto result = var + var2;
        ASSERT_EQ("x + y", result->print());
    }

    TEST(SumTestSuite, SameVarVarSum)
    {
        MC::FN::Variable var('x');
        auto result = var + var + var;
        ASSERT_EQ("3x", result->print());
    }

    TEST(SumTestSuite, ValPrimSum)
    {
        MC::FN::Value val(5);
        auto result = val + 5;
        ASSERT_EQ("10", result->print());
    }

    TEST(SumTestSuite, PrimValSum)
    {
        MC::FN::Value val(5);
        auto result = 5 + val;
        ASSERT_EQ("10", result.print());
    }

    TEST(SumTestSuite, SameValValSum)
    {
        MC::FN::Value val(5);
        auto result = val + val;
        ASSERT_EQ("10", result.print());
    }

/*
 *
 *              COMPLEX + VALUE TESTS
 *
 */

    TEST(SumTestSuite, SumValSum)
    {
        MC::FN::Variable var('x');
        auto result = (var + 5) + 6;
        ASSERT_EQ("x + 11", result->print());
    }

    TEST(SumTestSuite, ValSumSum)
    {
        MC::FN::Variable var('x');
        auto result = 6 + (5 + var);
        ASSERT_EQ("x + 11", result->print());
    }

    TEST(SumTestSuite, SumVarSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto result = (var + 5) + var2;
        ASSERT_EQ("x + y + 5", result->print());
    }

    TEST(SumTestSuite, VarSumSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto result = var + (5 + var2);
        ASSERT_EQ("x + y + 5", result->print());
    }

    TEST(SumTestSuite, VarMultSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var2 * 5;
        auto result = var + mult;
        ASSERT_EQ("x + 5y", result->print());
    }

    TEST(SumTestSuite, MultVarSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var2 * 5;
        auto result = mult + var;
        ASSERT_EQ("x + 5y", result->print());
    }

    TEST(SumTestSuite, ValMultSum)
    {
        MC::FN::Variable var2('y');
        auto mult = var2 * 5;
        auto result = 5 + mult;
        ASSERT_EQ("5y + 5", result->print());
    }

    TEST(SumTestSuite, MultValSum)
    {
        MC::FN::Variable var2('y');
        auto mult = var2 * 5;
        auto result = mult + 5;
        ASSERT_EQ("5y + 5", result->print());
    }


    TEST(SumTestSuite, VarDivSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto div = var2 / 5;
        auto result = var + div;
        ASSERT_EQ("x + 0.2y", result->print());
    }

    TEST(SumTestSuite, DivVarSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto div = var2 / 5;
        auto result = div + var;
        ASSERT_EQ("x + 0.2y", result->print());
    }

    TEST(SumTestSuite, ValDivSum)
    {
        MC::FN::Variable var2('y');
        auto div = var2 / 5;
        auto result = 5 + div;
        ASSERT_EQ("0.2y + 5", result->print());
    }

    TEST(SumTestSuite, DivValSum)
    {
        MC::FN::Variable var2('y');
        auto div = var2 / 5;
        auto result = div + 5;
        ASSERT_EQ("0.2y + 5", result->print());
    }

/*
 *
 *          COMPLEX + COMPLEX TESTS
 *
 */

    TEST(SumTestSuite, SumSumSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto result = (var + 6) + (5 + var2);
        ASSERT_EQ("x + y + 11", result->print());
    }

    TEST(SumTestSuite, MultMultSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var * 5;
        auto mult2 = var2 * 7;
        auto result = mult + mult2;
        ASSERT_EQ("5x + 7y", result->print());
    }

    TEST(SumTestSuite, MultSumSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var * 5;
        auto sum = var2 + 7;
        auto result = mult + sum;
        ASSERT_EQ("5x + y + 7", result->print());
    }

    TEST(SumTestSuite, SumMultSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var * 5;
        auto sum = var2 + 7;
        auto result = sum + mult;
        ASSERT_EQ("5x + y + 7", result->print());
    }

    TEST(SumTestSuite, MultDivSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var * 5;
        auto div = var2 / 7;
        auto result = mult + div;
        ASSERT_EQ("5x + 0.142857y", result->print());
    }

    TEST(SumTestSuite, DivMultSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto mult = var * 5;
        auto div = var2 / 7;
        auto result = div + mult;
        ASSERT_EQ("5x + 0.142857y", result->print());
    }

    TEST(SumTestSuite, DivDivSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto div = var / 5;
        auto div2 = var2 / 7;
        auto result = div + div2;
        ASSERT_EQ("0.2x + 0.142857y", result->print());
    }

    TEST(SumTestSuite, DivSumSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto div = var / 5;
        auto sum = var2 + 7;
        auto result = div + sum;
        ASSERT_EQ("0.2x + y + 7", result->print());
    }

    TEST(SumTestSuite, SumDivSum)
    {
        MC::FN::Variable var('x');
        MC::FN::Variable var2('y');
        auto div = var / 5;
        auto sum = var2 + 7;
        auto result = sum + div;
        ASSERT_EQ("0.2x + y + 7", result->print());
    }

/*
 *
 *                  SIMPLIFICATION TESTS
 *
 */

    TEST(SumTestSuite, TwoSameExpsSum)
    {
        using namespace MC::FN;

        Variable var('x');
        auto exp = var ^2;
        auto result = exp + exp;
        ASSERT_EQ("2(x ^ 2)", result->print());
    }

    TEST(SumTestSuite, TwoSameExpsInsideMultSum)
    {
        using namespace MC::FN;

        Variable x('x');
        auto exp = x ^ 2;
        auto sum = x + 5;
        auto mult = sum * exp;
        // x ^ 3 + 5x ^ 2
        auto rOp = mult + x;
        auto result = rOp + exp;
        ASSERT_EQ("x + x ^ 3 + 6(x ^ 2)", result->print());
    }

    TEST(SumTestSuite, UnityDivSum)
    {
        using namespace MC::FN;

        Variable var('x');
        auto div = var / var;
        auto result = (var + 1) + div;
        ASSERT_EQ("x + 2", result->print());
    }

    TEST(SumTestSuite, MultCommonCoreSum)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        auto minusOneOp = (x + 1);
        auto minusTwoOp = (y + 5);
        auto zeroOp = minusOneOp * minusTwoOp;
        // xy + y + 5x + 5
        auto firstOp = zeroOp * (x ^ 3);
        // (x + 1) * (x^3) * y + (5x + 5) * (x^3)
        auto secondSecondOp = x + 7;
        auto secondOp = minusTwoOp * secondSecondOp;
        auto result = firstOp + secondOp;
        ASSERT_EQ("5x + 7y + 5(x ^ 3) + y(x ^ 3) + 5(x ^ 4) + y(x ^ 4) + xy + 35", result->print());
    }

    TEST(SumTestSuite, MultCommonFullCoreSum)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = y * z;
        auto second = x * y * z;
        auto result = first + second;
        ASSERT_EQ("yz + xyz", result->print());
    }

/*
 *
 *                       MISCELLANEOUS
 *
 */

    TEST(SumTestSuite, Misc1)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto result = x + 1;
        ASSERT_EQ("x + 1", result->print());
    }

    TEST(SumTestSuite, Misc2)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = x + 1;
        auto result = first + x;
        ASSERT_EQ("2x + 1", result->print());
    }

    TEST(SumTestSuite, Misc3)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = y + 1;
        auto result = first + x;
        ASSERT_EQ("x + y + 1", result->print());
    }

    TEST(SumTestSuite, Misc4)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = x * y;
        auto result = first + x;
        ASSERT_EQ("x + xy", result->print());
    }

    TEST(SumTestSuite, Misc5)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = x * y * 2;
        auto result = first + x;
        ASSERT_EQ("x + 2xy", result->print());
    }

    TEST(SumTestSuite, Misc6)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = (x + 1) * y;
        auto result = first + x;
        ASSERT_EQ("x + y + xy", result->print());
    }

    TEST(SumTestSuite, Misc7)
    {
        using namespace MC::FN;

        Variable x('x');
        Variable y('y');
        Variable z('z');
        auto first = (x ^ 2) * y;
        auto result = first + x;
        ASSERT_EQ("x + y(x ^ 2)", result->print());
    }
}