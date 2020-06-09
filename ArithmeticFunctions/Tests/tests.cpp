//
// Created by mrhowever on 24.01.20.
//

#include "gtest/gtest.h"
#include "../include/ArithmeticFunctions.hh"
#include "../include/ArithmeticFunctionException.hh"
#include <chrono>
#include <cmath>

TEST(ArithmeticFunctionsTests, NormalPowTest)
{
    int a = 42;
    int b = 5;
    int c = MC::AF::pow(a,b);
    EXPECT_EQ(c,130691232);
}

TEST(ArithmeticFunctionsTests, DoublePowTest)
{
    double a = 2.77;
    int b = 5;
    double c = MC::AF::pow(a,b);
    EXPECT_FLOAT_EQ(c,163.079302516);
}

TEST(ArithmeticFunctionsTests, ZeroPowTest)
{
    int a = 42;
    int b = 0;
    int c = MC::AF::pow(a,b);
    EXPECT_EQ(c,1);
}

TEST(ArithmeticFunctionsTests, NegativeBasePowTest)
{
    int a = -42;
    int b = 5;
    int c = MC::AF::pow(a,b);
    EXPECT_EQ(c,-130691232);
}

TEST(ArithmeticFunctionsTests, ZeroBasePowTest)
{
    int a = 0;
    int b = 5;
    int c = MC::AF::pow(a,b);
    EXPECT_EQ(c,0);
}

TEST(ArithmeticFunctionsTests, MontgomeryLadderTest)
{
    int a = 15;
    int b = 4;
    int c = MC::AF::montgomeryLadder(a,b);
    EXPECT_EQ(c,50625);
}

TEST(ArithmeticFunctionsTests, MontgomeryLadderZeroPowTest)
{
    int a = 42;
    int b = 0;
    int c = MC::AF::montgomeryLadder(a,b);
    EXPECT_EQ(c,1);
}

TEST(ArithmeticFunctionsTests, MontgomeryLadderNegativeBasePowTest)
{
    int a = -42;
    int b = 5;
    int c = MC::AF::montgomeryLadder(a,b);
    EXPECT_EQ(c,-130691232);
}

TEST(ArithmeticFunctionsTests, MontgomeryLadderZeroBasePowTest)
{
    int a = 0;
    int b = 5;
    int c = MC::AF::montgomeryLadder(a,b);
    EXPECT_EQ(c,0);
}

TEST(ArithmeticFunctionsTests, PowTimeTest)
{
    int64_t a = 2;
    int64_t b = 63;

    auto start = std::chrono::high_resolution_clock::now();
    int64_t c = MC::AF::pow(a,b);
    auto end = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    int64_t c2 = std::pow(a,b);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    int64_t c3 = MC::AF::montgomeryLadder(a,b);
    auto end3 = std::chrono::high_resolution_clock::now();

    auto total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    auto total2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
    auto total3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count();

    std::cout<<std::endl<<std::endl<<"My implementation: "<<total<<" ns"<<std::endl
             <<"Montgomery ladder implementation: "<<total3<<" ns"<<std::endl
             <<"Built-in implementation: "<<total2<<" ns"<<std::endl;

    EXPECT_LT(total,total2);
}

TEST(ArithmeticFunctionsTests, NormalRootTest)
{
    int a = 30;
    int b = 3;
    double c = MC::AF::root(a,b);
    EXPECT_FLOAT_EQ(c,3.1072321);
}

TEST(ArithmeticFunctionsTests, ExactRootTest)
{
    int a = 9;
    int b = 2;
    double c = MC::AF::root(a,b);
    EXPECT_FLOAT_EQ(c,3.0);
}

TEST(ArithmeticFunctionsTests, ZeroRootTest)
{
    int a = 0;
    int b = 3;
    double c = MC::AF::root(a,b);
    EXPECT_FLOAT_EQ(c,0.0);
}

TEST(ArithmeticFunctionsTests, ZeroRootOrderTest)
{
    int a = 3;
    int b = 0;
    EXPECT_THROW(MC::AF::root(a,b), MC::AF::ArithmeticFunctionException);
}

TEST(ArithmeticFunctionsTests, RootTimeTest)
{
    int64_t a = 2;
    int64_t b = 63;

    auto start = std::chrono::high_resolution_clock::now();
    double c = MC::AF::root(a,b);
    auto end = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    double c2 = std::pow(a,1.0/b);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto total = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    auto total2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();

    std::cout<<std::endl<<std::endl<<"My implementation: "<<total<<" ns"<<std::endl
             <<"Built-in implementation: "<<total2<<" ns"<<std::endl;

    EXPECT_LT(total,total2);
}

TEST(ArithmeticFunctionsTests, EstimateTimeTest)
{
    double value = 79.0;

    double a = 0, b = 0, c = 0, d = 0, e = 0;
    double totalA = 0, totalB = 0, totalC = 0, totalD = 0, totalE = 0;
    double errorA = 0, errorB = 0, errorC = 0, errorD = 0, errorE = 0;
    uint64_t iterations = 3;

    for(uint64_t i = 0; i < iterations; i++) {
        double correctVal = std::sqrt(value);

        auto startA = std::chrono::high_resolution_clock::now();
        a = MC::AF::__initialEstimate(value, MC::AF::EstimationType::LINEAR);
        errorA += std::abs(correctVal-a)/correctVal;
        auto endA = std::chrono::high_resolution_clock::now();

        auto startB = std::chrono::high_resolution_clock::now();
        b = MC::AF::__initialEstimate(value, MC::AF::EstimationType::HYPERBOLIC);
        errorB += std::abs(correctVal-b)/correctVal;
        auto endB = std::chrono::high_resolution_clock::now();

        auto startC = std::chrono::high_resolution_clock::now();
        c = MC::AF::__initialEstimate(value, MC::AF::EstimationType::ARITHMETIC);
        errorC += std::abs(correctVal-c)/correctVal;
        auto endC = std::chrono::high_resolution_clock::now();

        auto startD = std::chrono::high_resolution_clock::now();
        d = MC::AF::__initialEstimate((double) value, MC::AF::EstimationType::BINARY);
        errorD += std::abs(correctVal-d)/correctVal;
        auto endD = std::chrono::high_resolution_clock::now();

        auto startE = std::chrono::high_resolution_clock::now();
        e = MC::AF::__initialEstimate((float) value, MC::AF::EstimationType::FLOAT);
        errorE += std::abs(correctVal-e)/correctVal;
        auto endE = std::chrono::high_resolution_clock::now();

        totalA += std::chrono::duration_cast<std::chrono::nanoseconds>(endA - startA).count();
        totalB += std::chrono::duration_cast<std::chrono::nanoseconds>(endB - startB).count();
        totalC += std::chrono::duration_cast<std::chrono::nanoseconds>(endC - startC).count();
        totalD += std::chrono::duration_cast<std::chrono::nanoseconds>(endD - startD).count();
        totalE += std::chrono::duration_cast<std::chrono::nanoseconds>(endE - startE).count();

        value *= 13;
    }

    totalA /= iterations;
    totalB /= iterations;
    totalC /= iterations;
    totalD /= iterations;
    totalE /= iterations;
    errorA /= iterations;
    errorB /= iterations;
    errorC /= iterations;
    errorD /= iterations;
    errorE /= iterations;

    std::cout<<std::endl<<std::endl<<"Implementation A: "<<a<<" Error: "<<errorA<<"% Time "<<totalA<<" ns"<<std::endl
             <<"Implementation B: "<<b<<" Error: "<<errorB<<"% Time "<<totalB<<" ns"<<std::endl
            <<"Implementation C: "<<c<<" Error: "<<errorC<<"% Time "<<totalC<<" ns"<<std::endl
            <<"Implementation D: "<<d<<" Error: "<<errorD<<"% Time "<<totalD<<" ns"<<std::endl
            <<"Implementation E: "<<e<<" Error: "<<errorE<<"% Time "<<totalE<<" ns"<<std::endl;

    EXPECT_EQ(1,1);
}

TEST(ArithmeticFunctionsTests, BabylonianRootTest)
{
    int a = 30;
    double c = MC::AF::__babylonianSqrt(a);
    EXPECT_FLOAT_EQ(c, 5.47722557505);
}

TEST(ArithmeticFunctionsTests, TwoVarRootTest)
{
    double a = 2.59;
    double c = MC::AF::__twoVarSqrt(a);
    EXPECT_FLOAT_EQ(c, 1.6093476939431081);
}

TEST(ArithmeticFunctionsTests, NewtonRootTest)
{
    int a = 30;
    double c = MC::AF::__newtonSqrt(a);
    EXPECT_FLOAT_EQ(c, 5.47722557505);
}

TEST(ArithmeticFunctionsTests, HalleyRootTest)
{
    int a = 30;
    double c = MC::AF::__halleySqrt(a);
    EXPECT_FLOAT_EQ(c, 5.47722557505);
}

TEST(ArithmeticFunctionsTests, GoldschmidtRootTest)
{
    int a = 30;
    double c = MC::AF::__goldschmidtSqrt(a);
    EXPECT_FLOAT_EQ(c, 5.47722557505);
}

TEST(ArithmeticFunctionsTests, GoldschmidtReciprocalRootTest)
{
    int a = 30;
    //double c = MC::AF::__goldschmidtSqrt(a);
    double c = MC::AF::__initialEstimate(a,MC::AF::FLOAT_RECIPROCAL);
    EXPECT_FLOAT_EQ(c, MC::AF::__goldschmidtSqrtReciprocal(a));
}

TEST(ArithmeticFunctionsTests, FusedGoldschmidtRootTest)
{
    int a = 30;
    double c = MC::AF::__fusedGoldschmidtSqrt(a);
    EXPECT_FLOAT_EQ(c, 5.47722557505);
}

TEST(ArithmeticFunctionsTests, FusedGoldschmidtReciprocalRootTest)
{
    int a = 30;
    double c = MC::AF::__fusedGoldschmidtSqrt(a);
    EXPECT_FLOAT_EQ(1.0/c, MC::AF::__fusedGoldschmidtSqrtReciprocal(a));
}

TEST(ArithmeticFunctionsTests, FractionRootTest)
{
    int a = 30;
    double c = MC::AF::__fractionExpansionSqrt(a);
    EXPECT_FLOAT_EQ(c,5.47722557505);
}