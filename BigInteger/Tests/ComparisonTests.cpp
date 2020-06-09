//
// Created by mrhowever on 21.10.19.
//

#include "gtest/gtest.h"
#include "../BigInteger.hh"
#include "../BigInteger.tcc"
#include "../BigIntegerComparisons.tcc"
#include "../InvalidStringInputException.hh"
#include <limits.h>
#include <random>

TEST(ComparisonTestSuite, PosSmallSmallEQTrue) {
    BigInteger integer1(80);
    BigInteger integer2(80);
    ASSERT_TRUE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallEQFalse) {
    BigInteger integer1(80);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallEQTrue) {
    BigInteger integer1(-80);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallEQFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosNegSmallSmallEQFalse) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosSmallZeroEQFalse) {
    BigInteger integer1(80);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegSmallZeroEQFalse) {
    BigInteger integer1(-80);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosBigBigEQTrue) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("739853678349563278956347856832479349856832475698",10);
    ASSERT_TRUE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosBigBigEQFalse) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("37839853678349563278956347856832479349856832478",10);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegBigBigEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("-739853678349563278956347856832479349856832475698",10);
    ASSERT_TRUE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegBigBigEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("-37839853678349563278956347856832479349856832478",10);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("739853678349563278956347856832479349856832475698",10);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosBigZeroEQFalse) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegBigZeroEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosBigSmallEQFalse) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(560);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegBigSmallEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(-560);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosNegBigSmallEQFalse) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(-560);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, NegPosBigSmallEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(560);
    ASSERT_FALSE(integer1 == integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallNEQFalse) {
    BigInteger integer1(80);
    BigInteger integer2(80);
    ASSERT_FALSE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallNEQTrue) {
    BigInteger integer1(80);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallNEQFalse) {
    BigInteger integer1(-80);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallNEQTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosNegSmallSmallNEQTrue) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosSmallZeroNEQTrue) {
    BigInteger integer1(80);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegSmallZeroNEQTrue) {
    BigInteger integer1(-80);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosBigBigNEQFalse) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("739853678349563278956347856832479349856832475698",10);
    ASSERT_FALSE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosBigBigNEQTrue) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("37839853678349563278956347856832479349856832478",10);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegBigBigNEQFalse) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("-739853678349563278956347856832479349856832475698",10);
    ASSERT_FALSE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegBigBigNEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("-37839853678349563278956347856832479349856832478",10);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigNEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2("739853678349563278956347856832479349856832475698",10);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosBigZeroNEQTrue) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegBigZeroNEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosBigSmallNEQTrue) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(560);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegBigSmallNEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(-560);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosNegBigSmallNEQTrue) {
    BigInteger integer1("739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(-560);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, NegPosBigSmallNEQTrue) {
    BigInteger integer1("-739853678349563278956347856832479349856832475698",10);
    BigInteger integer2(560);
    ASSERT_TRUE(integer1 != integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallGTTestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosSmallSmallGTTestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallEqualGTTestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallGTTestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallGTTestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, NegSmallSmallEqualGTTestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallGTTestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallGTTestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, ZeroSmallGTTestTrue) {
    BigInteger integer1(0);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 > integer1);
}

TEST(ComparisonTestSuite, ZeroSmallGTTestFalse) {
    BigInteger integer1(0);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallEqualGTTestFalse) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosBigBigGTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosBigBigGTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosBigBigEqualGTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, NegBigBigGTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, NegBigBigGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, NegBigBigEqualGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer2 > integer1);
}

TEST(ComparisonTestSuite, PosNegBigBigGTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigEqualGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, BigBigZeroGTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, BigBigZeroGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosSmallBigGTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosSmallBigGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, NegSmallBigGTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer1 > integer2);
}

TEST(ComparisonTestSuite, NegSmallBigGTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer1 > integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallGTETestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosSmallSmallGTETestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallEqualGTETestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallGTETestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallGTETestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, NegSmallSmallEqualGTETestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallGTETestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallGTETestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, ZeroSmallGTETestTrue) {
    BigInteger integer1(0);
    BigInteger integer2(80);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, ZeroSmallGTETestFalse) {
    BigInteger integer1(0);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallEqualGTETestFalse) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosBigBigGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosBigBigGTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosBigBigEqualGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, NegBigBigGTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, NegBigBigGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, NegBigBigEqualGTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer2 >= integer1);
}

TEST(ComparisonTestSuite, PosNegBigBigGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigEqualGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, BigBigZeroGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, BigBigZeroGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosSmallBigGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, PosSmallBigGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, NegSmallBigGTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer1 >= integer2);
}

TEST(ComparisonTestSuite, NegSmallBigGTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer1 >= integer2);
}

/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

TEST(ComparisonTestSuite, PosSmallSmallLTTestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosSmallSmallLTTestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallEqualLTTestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallLTTestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallLTTestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 < integer1);
}

TEST(ComparisonTestSuite, NegSmallSmallEqualLTTestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallLTTestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallLTTestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 < integer1);
}

TEST(ComparisonTestSuite, ZeroSmallLTTestFalse) {
    BigInteger integer1(0);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, ZeroSmallLTTestTrue) {
    BigInteger integer1(0);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallEqualLTTestTrue) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosBigBigLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosBigBigLTTestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosBigBigEqualLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, NegBigBigLTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, NegBigBigLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer2 < integer1);
}

TEST(ComparisonTestSuite, NegBigBigEqualLTTestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-438724682374682746783246783264872364876238476238",10);
    ASSERT_FALSE(integer2 < integer1);
}

TEST(ComparisonTestSuite, PosNegBigBigLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigEqualLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, BigBigZeroLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, BigBigZeroLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosSmallBigLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosSmallBigLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, NegSmallBigLTTestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer1 < integer2);
}

TEST(ComparisonTestSuite, NegSmallBigLTTestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer1 < integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallLTETestFalse) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosSmallSmallLTETestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(80);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosSmallSmallEqualLTETestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallLTETestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, NegSmallSmallLTETestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, NegSmallSmallEqualLTETestTrue) {
    BigInteger integer1(-50);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallLTETestFalse) {
    BigInteger integer1(-50);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallLTETestTrue) {
    BigInteger integer1(50);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, ZeroSmallLTETestFalse) {
    BigInteger integer1(0);
    BigInteger integer2(80);
    ASSERT_FALSE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, ZeroSmallLTETestTrue) {
    BigInteger integer1(0);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosNegSmallSmallEqualLTETestTrue) {
    BigInteger integer1(80);
    BigInteger integer2(-80);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosBigBigLTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosBigBigLTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosBigBigEqualLTETestTrue) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, NegBigBigLTETestFalse) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, NegBigBigLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, NegBigBigEqualLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer2 <= integer1);
}

TEST(ComparisonTestSuite, PosNegBigBigLTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("-43763485634785634785673485673485673485683465783465873",10);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("43763485634785634785673485673485673485683465783465873",10);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosNegBigBigEqualLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2("438724682374682746783246783264872364876238476238",10);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, BigBigZeroLTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, BigBigZeroLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(0);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosSmallBigLTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosSmallBigLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(50);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, NegSmallBigLTETestFalse) {
    BigInteger integer1("438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_FALSE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, NegSmallBigLTETestTrue) {
    BigInteger integer1("-438724682374682746783246783264872364876238476238",10);
    BigInteger integer2(-50);
    ASSERT_TRUE(integer1 <= integer2);
}

TEST(ComparisonTestSuite, PosSmallIntGTTestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer > 30);
}

TEST(ComparisonTestSuite, PosSmallIntGTTestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer > 130);
}

TEST(ComparisonTestSuite, PosBigIntGTTestTrue) {
    BigInteger integer("43678564387563478568365",10);
    ASSERT_TRUE(integer > 30);
}

TEST(ComparisonTestSuite, NegSmallIntGTTestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer > -150);
}

TEST(ComparisonTestSuite, NegSmallIntGTTestFalse) {
    BigInteger integer(-110);
    ASSERT_FALSE(integer > -15);
}

TEST(ComparisonTestSuite, NegBigIntGTTestFalse) {
    BigInteger integer("-634783675834657843857938975",10);
    ASSERT_FALSE(integer > -150);
}

TEST(ComparisonTestSuite, PosSmallIntEqualGTTestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer > 120);
}

TEST(ComparisonTestSuite, NegSmallIntEqualGTTestFalse) {
    BigInteger integer(-120);
    ASSERT_FALSE(integer > -120);
}

TEST(ComparisonTestSuite, PosNegSmallIntGTTestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer > -150);
}

TEST(ComparisonTestSuite, PosNegBigIntGTTestTrue) {
    BigInteger integer("734347583485634786534786538",10);
    ASSERT_TRUE(integer > -150);
}

TEST(ComparisonTestSuite, NegPosSmallIntGTTestFalse) {
    BigInteger integer(-190);
    ASSERT_FALSE(integer > -150);
}

TEST(ComparisonTestSuite, NegPosBigIntGTTestFalse) {
    BigInteger integer("-734347583485634786534786538",10);
    ASSERT_FALSE(integer > 150);
}

TEST(ComparisonTestSuite, PosNegBigIntEqualGTTestTrue) {
    BigInteger integer(150);
    ASSERT_TRUE(integer > -150);
}

TEST(ComparisonTestSuite, NegPosBigIntEqualGTTestFalse) {
    BigInteger integer(-150);
    ASSERT_FALSE(integer > 150);
}

TEST(ComparisonTestSuite, PosSmallIntGTETestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer >= 30);
}

TEST(ComparisonTestSuite, PosSmallIntGTETestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer >= 130);
}

TEST(ComparisonTestSuite, PosBigIntGTETestTrue) {
    BigInteger integer("43678564387563478568365",10);
    ASSERT_TRUE(integer >= 30);
}

TEST(ComparisonTestSuite, NegSmallIntGTETestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer >= -150);
}

TEST(ComparisonTestSuite, NegSmallIntGTETestFalse) {
    BigInteger integer(-120);
    ASSERT_FALSE(integer >= -15);
}

TEST(ComparisonTestSuite, NegBigIntGTETestFalse) {
    BigInteger integer("-634783675834657843857938975",10);
    ASSERT_FALSE(integer >= -150);
}

TEST(ComparisonTestSuite, PosSmallIntEqualGTETestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer >= 120);
}

TEST(ComparisonTestSuite, NegSmallIntEqualGTETestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer >= -120);
}

TEST(ComparisonTestSuite, PosNegSmallIntGTETestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer >= -150);
}

TEST(ComparisonTestSuite, PosNegBigIntGTETestTrue) {
    BigInteger integer("734347583485634786534786538",10);
    ASSERT_TRUE(integer >= -150);
}

TEST(ComparisonTestSuite, NegPosSmallIntGTETestFalse) {
    BigInteger integer(-190);
    ASSERT_FALSE(integer >= -150);
}

TEST(ComparisonTestSuite, NegPosBigIntGTETestFalse) {
    BigInteger integer("-734347583485634786534786538",10);
    ASSERT_FALSE(integer >= 150);
}

TEST(ComparisonTestSuite, PosNegBigIntEqualGTETestTrue) {
    BigInteger integer(150);
    ASSERT_TRUE(integer >= -150);
}

TEST(ComparisonTestSuite, NegPosBigIntEqualGTETestFalse) {
    BigInteger integer(-150);
    ASSERT_FALSE(integer >= 150);
}












TEST(ComparisonTestSuite, PosSmallIntLTTestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer < 30);
}

TEST(ComparisonTestSuite, PosSmallIntLTTestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer < 130);
}

TEST(ComparisonTestSuite, PosBigIntLTTestFalse) {
    BigInteger integer("43678564387563478568365",10);
    ASSERT_FALSE(integer < 30);
}

TEST(ComparisonTestSuite, NegSmallIntLTTestFalse) {
    BigInteger integer(-120);
    ASSERT_FALSE(integer < -150);
}

TEST(ComparisonTestSuite, NegSmallIntLTTestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer < -15);
}

TEST(ComparisonTestSuite, NegBigIntLTTestTrue) {
    BigInteger integer("-634783675834657843857938975",10);
    ASSERT_TRUE(integer < -150);
}

TEST(ComparisonTestSuite, PosSmallIntEqualLTTestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer < 120);
}

TEST(ComparisonTestSuite, NegSmallIntEqualLTTestFalse) {
    BigInteger integer(-120);
    ASSERT_FALSE(integer < -120);
}

TEST(ComparisonTestSuite, PosNegSmallIntLTTestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer < -150);
}

TEST(ComparisonTestSuite, PosNegBigIntLTTestFalse) {
    BigInteger integer("734347583485634786534786538",10);
    ASSERT_FALSE(integer < -150);
}

TEST(ComparisonTestSuite, NegPosSmallIntLTTestTrue) {
    BigInteger integer(-190);
    ASSERT_TRUE(integer < -150);
}

TEST(ComparisonTestSuite, NegPosBigIntLTTestTrue) {
    BigInteger integer("-734347583485634786534786538",10);
    ASSERT_TRUE(integer < 150);
}

TEST(ComparisonTestSuite, PosNegBigIntEqualLTTestFalse) {
    BigInteger integer(150);
    ASSERT_FALSE(integer < -150);
}

TEST(ComparisonTestSuite, NegPosBigIntEqualLTTestTrue) {
    BigInteger integer(-150);
    ASSERT_TRUE(integer < 150);
}

TEST(ComparisonTestSuite, PosSmallIntLTETestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer <= 30);
}

TEST(ComparisonTestSuite, PosSmallIntLTETestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer <= 130);
}

TEST(ComparisonTestSuite, PosBigIntLTETestFalse) {
    BigInteger integer("43678564387563478568365",10);
    ASSERT_FALSE(integer <= 30);
}

TEST(ComparisonTestSuite, NegSmallIntLTETestFalse) {
    BigInteger integer(-120);
    ASSERT_FALSE(integer <= -150);
}

TEST(ComparisonTestSuite, NegSmallIntLTETestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer <= -15);
}

TEST(ComparisonTestSuite, NegBigIntLTETestTrue) {
    BigInteger integer("-634783675834657843857938975",10);
    ASSERT_TRUE(integer <= -150);
}

TEST(ComparisonTestSuite, PosSmallIntEqualLTETestTrue) {
    BigInteger integer(120);
    ASSERT_TRUE(integer <= 120);
}

TEST(ComparisonTestSuite, NegSmallIntEqualLTETestTrue) {
    BigInteger integer(-120);
    ASSERT_TRUE(integer <= -120);
}

TEST(ComparisonTestSuite, PosNegSmallIntLTETestFalse) {
    BigInteger integer(120);
    ASSERT_FALSE(integer <= -150);
}

TEST(ComparisonTestSuite, PosNegBigIntLTETestFalse) {
    BigInteger integer("734347583485634786534786538",10);
    ASSERT_FALSE(integer <= -150);
}

TEST(ComparisonTestSuite, NegPosSmallIntLTETestTrue) {
    BigInteger integer(-190);
    ASSERT_TRUE(integer <= -150);
}

TEST(ComparisonTestSuite, NegPosBigIntLTETestTrue) {
    BigInteger integer("-734347583485634786534786538",10);
    ASSERT_TRUE(integer <= 150);
}

TEST(ComparisonTestSuite, PosNegBigIntEqualLTETestFalse) {
    BigInteger integer(150);
    ASSERT_FALSE(integer <= -150);
}

TEST(ComparisonTestSuite, NegPosBigIntEqualLTETestTrue) {
    BigInteger integer(-150);
    ASSERT_TRUE(integer <= 150);
}