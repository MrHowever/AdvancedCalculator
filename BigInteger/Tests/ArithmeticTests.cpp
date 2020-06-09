//
// Created by mrhowever on 24.10.19.
//


#include <chrono>
#include "gtest/gtest.h"
#include "../BigInteger.hh"
#include "../BigIntegerArithmeticOperations.tcc"
#include "../FourierTransform.hh"
#include "../../Prime/Prime.hh"
#include "../../Prime/Prime.cpp"
#include "../../Transforms/NumberTheoreticTransform.hh"
#include "../../Transforms/FermatNumberTransform.hh"
#include "../../Transforms/MersenneNumberTransform.hh"
#include "../../Transforms/NumberTheoreticTransform.cpp"
#include "../../Transforms/FermatNumberTransform.cpp"
#include "../../Transforms/MersenneNumberTransform.cpp"

TEST(ArithmeticTestsSuite, KaratsubaMultBaseCaseTest) {
    BigInteger integer1("894632746329784632789462379489",10);
        BigInteger integer2("893475983475897348957348975983",10);

    BigInteger result(integer1.karatsubaMultiplication(integer2));

    EXPECT_EQ(result.toString(),"799332872876747319228635915290790621245506189008896692812687");
}

TEST(ArithmeticTestsSuite, KaratsubaMultBigNumberTest) {
    BigInteger integer1("89463274632963847563475683475683756783435784632789462379489",10);
    BigInteger integer2("89347598347589734895743685756347856347856437856873348975983",10);

    BigInteger result(integer1.karatsubaMultiplication(integer2));

    EXPECT_EQ(result.toString(),"7993328728766167313211719615729111289785055220042406299065458769702039473988060357634250998131850022189543820692812687");
}

TEST(ArithmeticTestsSuite, ToomCookMultBigNumberTest) {
    BigInteger integer1("89463274632963847563475683475685839783497553485789347598343756783435784632789462379489",10);
    BigInteger integer2("89347598347589734895743685756347856347435783894759834758934759543856437856873348975983",10);

    BigInteger result(integer1.toomCookMultiplication(integer2));

    EXPECT_EQ(result.toString(),"7993328728766167313211719615729297400800299067190413499127437641597750100935906298017088175939247245639203604122123814821130681253482189225947637078694022189543820692812687");
}

TEST(ArithmeticTestSuite, SingleDigitDivision) {
    BigInteger big("398623478963274832874632984632894632784963247832647892367489326487932648793246987289",10);
    uint64_t small = 19361827367821963;

    BigInteger result(big / small);
    EXPECT_EQ(result.toString(), "20588112443650844488294027125686798783998906503821003683101845251441");
}

TEST(ArithmeticTestsSuite, NTTTest) {
    std::vector<uint64_t> digits = {8,7,6,5,0};

    MC::MT::NTT<uint64_t> transformer(digits,0,337);

    auto result = transformer.transform(digits);
    auto result2 = transformer.inverseTransform(result);

    EXPECT_EQ(result[0],26);
    EXPECT_EQ(result[1],24);
    EXPECT_EQ(result[2],298);
    EXPECT_EQ(result[3],322);
    EXPECT_EQ(result[4],2);
    EXPECT_EQ(result[5],83);
    EXPECT_EQ(result[6],43);
    EXPECT_EQ(result[7],277);

    EXPECT_EQ(result2[0],8);
    EXPECT_EQ(result2[1],7);
    EXPECT_EQ(result2[2],6);
    EXPECT_EQ(result2[3],5);
    EXPECT_EQ(result2[4],0);
    EXPECT_EQ(result2[5],0);
    EXPECT_EQ(result2[6],0);
    EXPECT_EQ(result2[7],0);
}

TEST(ArithmeticTestsSuite, FTTTest) {
    std::vector<uint64_t> digits = {8,7,6,5,0};
    auto result = MC::FT::fnt(digits, (uint64_t) std::round(std::pow(2,6)) + 1);
    auto result2 = MC::FT::ifnt<uint64_t>(result.first,(uint64_t) std::round(std::pow(2,6)) + 1);

    EXPECT_EQ(digits[0],result2[0]);
    EXPECT_EQ(digits[1],result2[1]);
    EXPECT_EQ(digits[2],result2[2]);
    EXPECT_EQ(digits[3],result2[3]);
    EXPECT_EQ(digits[4],result2[4]);
    EXPECT_EQ(digits[5],result2[5]);
    EXPECT_EQ(digits[6],result2[6]);
    EXPECT_EQ(digits[7],result2[7]);
}

TEST(ArithmeticTestSuite,FermatModTest){
    auto start = std::chrono::high_resolution_clock::now();
    EXPECT_EQ(MC::MO::fermatMod(6,2,5), 1);
    EXPECT_EQ(MC::MO::fermatMod(2,2,5), 2);
    EXPECT_EQ(MC::MO::fermatMod(10,3,9),1);
    EXPECT_EQ(MC::MO::fermatMod(656,3,9),8);
}

TEST(ArithmeticTestSuite, FFTMultTest) {
    BigInteger integer(std::vector<uint64_t>{8,7,6,5,0});
    BigInteger integer2(std::vector<uint64_t>{4,3,2,1,0});
    BigInteger result = integer.fftMultiplication(integer2);

//    std::string int1 = integer.toString();
 //   std::string int2 = integer2.toString();
  //  std::string res = result.toString();

    EXPECT_EQ(1,1);

}