//
// Created by mrhowever on 16.10.19.
//

#include "gtest/gtest.h"
#include "../BigInteger.hh"
#include "../BigInteger.tcc"
#include "../InvalidStringInputException.hh"
#include <limits.h>
#include <random>

#define LOOPS 100

TEST(ConstructorTestsSuite, UintConstructorTest) {
    BigInteger integer(10);
    BigInteger integer2(std::numeric_limits<uint64_t>::max() - 1);
    BigInteger integer3(std::numeric_limits<uint64_t>::max());
    BigInteger integer4(0);

    EXPECT_EQ(integer.toString(),"10");
    EXPECT_EQ(integer2.toString(),std::to_string(std::numeric_limits<uint64_t>::max() - 1));
    EXPECT_EQ(integer3.toString(),std::to_string(std::numeric_limits<uint64_t>::max()));
    EXPECT_EQ(integer4.toString(),"0");
}

TEST(ConstructorTestsSuite, IntConstructorTest) {
    BigInteger integer(10);
    BigInteger integer2(std::numeric_limits<int64_t>::max());
    BigInteger integer3(std::numeric_limits<int64_t>::max() - 1);
    BigInteger integer4(std::numeric_limits<int64_t>::min());
    BigInteger integer5(std::numeric_limits<int64_t>::min() + 1);
    BigInteger integer6(0);
    BigInteger integer7(-50);

    EXPECT_EQ(integer.toString(),"10");
    EXPECT_EQ(integer2.toString(),std::to_string(std::numeric_limits<int64_t>::max()));
    EXPECT_EQ(integer3.toString(),std::to_string(std::numeric_limits<int64_t>::max() - 1));
    EXPECT_EQ(integer4.toString(),std::to_string(std::numeric_limits<int64_t>::min()));
    EXPECT_EQ(integer5.toString(),std::to_string(std::numeric_limits<int64_t>::min() + 1));
    EXPECT_EQ(integer6.toString(),"0");
    EXPECT_EQ(integer7.toString(),"-50");
}

TEST(ConstructorTestsSuite, StringConstructorTest) {
    BigInteger integer("10",10);
    BigInteger integer2("10234786247863278",10);
    BigInteger integer3("-95746387568373",10);
    BigInteger integer4("10234786243427632783246827346278634782364877863278",10);
    BigInteger integer5("-63478326478326947326478329467324637289643278946328946",10);

    EXPECT_EQ(integer.toString(),"10");
    EXPECT_EQ(integer2.toString(),"10234786247863278");
    EXPECT_EQ(integer3.toString(),"-95746387568373");
    EXPECT_EQ(integer4.toString(),"10234786243427632783246827346278634782364877863278");
    EXPECT_EQ(integer5.toString(),"-63478326478326947326478329467324637289643278946328946");
}

TEST(ConstructorTestsSuite, CopyConstructorTest) {
    BigInteger integer("173868273687126378216378126378621783632187",10);
    BigInteger copy(integer);
    BigInteger integer2("-2317867218368723678213687126387216378216837",10);
    BigInteger copy2(integer2);
    BigInteger integer3("1738682787",10);
    BigInteger copy3(integer3);
    BigInteger integer4("-23178676837",10);
    BigInteger copy4(integer4);

    EXPECT_EQ(integer.toString(), copy.toString());
    EXPECT_EQ(integer2.toString(), copy2.toString());
    EXPECT_EQ(integer3.toString(), copy3.toString());
    EXPECT_EQ(integer4.toString(), copy4.toString());
}

TEST(ConstructorTestsSuite, MoveConstructorTest) {
    BigInteger integer("173868273687126378216378126378621783632187",10);
    BigInteger copy(std::move(integer));
    BigInteger integer2("-2317867218368723678213687126387216378216837",10);
    BigInteger copy2(std::move(integer2));
    BigInteger integer3("1738682787",10);
    BigInteger copy3(std::move(integer3));
    BigInteger integer4("-23178676837",10);
    BigInteger copy4(std::move(integer4));

    EXPECT_EQ(copy.toString(), "173868273687126378216378126378621783632187");
    EXPECT_EQ(copy2.toString(), "-2317867218368723678213687126387216378216837");
    EXPECT_EQ(copy3.toString(), "1738682787");
    EXPECT_EQ(copy4.toString(), "-23178676837");

    EXPECT_EQ(integer.toString(), "0");
    EXPECT_EQ(integer2.toString(), "0");
    EXPECT_EQ(integer3.toString(), "0");
    EXPECT_EQ(integer4.toString(), "0");
}

TEST(ConstructorTestsSuite, UintAssignmentTest) {
    uint64_t val = 10;
    uint64_t val1 = std::numeric_limits<uint64_t>::max() - 1;
    uint64_t val2 = std::numeric_limits<uint64_t>::max();
    uint64_t val3 = 0;

    BigInteger integer;
    integer = val;
    BigInteger integer2;
    integer2 = val1;
    BigInteger integer3;
    integer3 = val2;
    BigInteger integer4;
    integer4 = val3;

    EXPECT_EQ(integer.toString(),"10");
    EXPECT_EQ(integer2.toString(),std::to_string(std::numeric_limits<uint64_t>::max() - 1));
    EXPECT_EQ(integer3.toString(),std::to_string(std::numeric_limits<uint64_t>::max()));
    EXPECT_EQ(integer4.toString(),"0");
}

TEST(ConstructorTestsSuite, IntAssignmentTest) {
    int64_t val = 10;
    int64_t val1 = std::numeric_limits<int64_t>::max();
    int64_t val2 = std::numeric_limits<int64_t>::max() - 1;
    int64_t val3 = std::numeric_limits<int64_t>::min();
    int64_t val4 = std::numeric_limits<int64_t>::min() + 1;
    int64_t val5 = 0;
    int64_t val6 = -50;

    BigInteger integer;
    integer = val;
    BigInteger integer2;
    integer2 = val1;
    BigInteger integer3;
    integer3 = val2;
    BigInteger integer4;
    integer4 = val3;
    BigInteger integer5;
    integer5 = val4;
    BigInteger integer6;
    integer6 = val5;
    BigInteger integer7;
    integer7 = val6;

    EXPECT_EQ(integer.toString(),"10");
    EXPECT_EQ(integer2.toString(),std::to_string(std::numeric_limits<int64_t>::max()));
    EXPECT_EQ(integer3.toString(),std::to_string(std::numeric_limits<int64_t>::max() - 1));
    EXPECT_EQ(integer4.toString(),std::to_string(std::numeric_limits<int64_t>::min()));
    EXPECT_EQ(integer5.toString(),std::to_string(std::numeric_limits<int64_t>::min() + 1));
    EXPECT_EQ(integer6.toString(),"0");
    EXPECT_EQ(integer7.toString(),"-50");
}

TEST(ConstructorTestsSuite, CopyAssignmentTest) {
    BigInteger integer("173868273687126378216378126378621783632187",10);
    BigInteger copy;
    copy = integer;
    BigInteger integer2("-2317867218368723678213687126387216378216837",10);
    BigInteger copy2;
    copy2 = integer2;
    BigInteger integer3("1738682787",10);
    BigInteger copy3;
    copy3 = integer3;
    BigInteger integer4("-23178676837",10);
    BigInteger copy4;
    copy4 = integer4;

    EXPECT_EQ(integer.toString(), copy.toString());
    EXPECT_EQ(integer2.toString(), copy2.toString());
    EXPECT_EQ(integer3.toString(), copy3.toString());
    EXPECT_EQ(integer4.toString(), copy4.toString());
}

TEST(ConstructorTestsSuite, MoveAssignmentTest) {
    BigInteger integer("173868273687126378216378126378621783632187",10);
    BigInteger copy;
    copy = std::move(integer);
    BigInteger integer2("-2317867218368723678213687126387216378216837",10);
    BigInteger copy2;
    copy2 = std::move(integer2);
    BigInteger integer3("1738682787",10);
    BigInteger copy3;
    copy3 = std::move(integer3);
    BigInteger integer4("-23178676837",10);
    BigInteger copy4;
    copy4 = std::move(integer4);

    EXPECT_EQ(copy.toString(), "173868273687126378216378126378621783632187");
    EXPECT_EQ(copy2.toString(), "-2317867218368723678213687126387216378216837");
    EXPECT_EQ(copy3.toString(), "1738682787");
    EXPECT_EQ(copy4.toString(), "-23178676837");

    EXPECT_EQ(integer.toString(), "0");
    EXPECT_EQ(integer2.toString(), "0");
    EXPECT_EQ(integer3.toString(), "0");
    EXPECT_EQ(integer4.toString(), "0");
}

TEST(ConstructorTestsSuite, RandomInputTest) {
    std::random_device device;
    std::mt19937_64 generator(device());
    std::uniform_int_distribution<std::mt19937::result_type> uintDistribution(std::numeric_limits<int64_t>::min(),std::numeric_limits<int64_t>::max());
    std::uniform_int_distribution<std::mt19937::result_type> intDistribution(std::numeric_limits<uint64_t>::min(),std::numeric_limits<uint64_t>::max());
    std::uniform_int_distribution<std::mt19937::result_type> stringBaseDistribution(2,32);
    std::uniform_int_distribution<std::mt19937::result_type> stringLengthDistribution(0,1000);
    std::uniform_int_distribution<std::mt19937::result_type> stringNegativeDistribution(0,1);


    for(int i = 0; i < LOOPS; i++) {
        uint64_t uintVal = uintDistribution(generator);
        int64_t intVal = intDistribution(generator);

        BigInteger signedInt(intVal);
        BigInteger unsignedInt(uintVal);
        BigInteger signedAssignment;
        signedAssignment = intVal;
        BigInteger unsignedAssignment;
        unsignedAssignment = uintVal;

        std::string number;
        uint64_t stringLength = stringLengthDistribution(generator);
        uint8_t stringBase = stringBaseDistribution(generator);

        std::uniform_int_distribution<std::mt19937::result_type> stringDistribution(0,stringBase-1);

        for(int j = 0; j < stringLength; j++) {
            int digit = stringDistribution(generator);

            if(j == 0 && digit == 0)
                digit = 1;

            if(digit < 10)
                number.append(std::to_string(digit));
            else
                number.append(std::to_string((char) (digit + 55)));
        }

        if(stringNegativeDistribution(generator)) {
            number = "-" + number;
        }

        BigInteger stringCheck(number,stringBase);

        EXPECT_EQ(signedInt.toString(), std::to_string(intVal));
        EXPECT_EQ(unsignedInt.toString(), std::to_string(uintVal));
        EXPECT_EQ(signedAssignment.toString(), std::to_string(intVal));
        EXPECT_EQ(unsignedAssignment.toString(), std::to_string(uintVal));
        EXPECT_EQ(stringCheck.toString(stringBase),number);
    }
}

TEST(ConstructorTestSuite, WrongInputTest) {
    ASSERT_THROW(BigInteger("źfweuhiewwi",10), InvalidStringInputException);
    ASSERT_THROW(BigInteger("74367856347856",2), InvalidStringInputException);
    ASSERT_THROW(BigInteger("0000",1), InvalidStringInputException);
    ASSERT_THROW(BigInteger("32984",0), InvalidStringInputException);
    ASSERT_THROW(BigInteger("32984",-20), InvalidStringInputException);
}