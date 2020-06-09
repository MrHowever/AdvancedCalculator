//
// Created by mrhowever on 20.10.19.
//

#include "gtest/gtest.h"
#include "../BigInteger.hh"
#include "../BigInteger.tcc"
#include "../ConversionFailedException.hh"
#include "../BigIntegerComparisons.tcc"
#include <limits.h>

TEST(ConversionTestSuite, Int8ConversionTest) {
    BigInteger integer(std::numeric_limits<int8_t>::max());
    BigInteger integer1(std::numeric_limits<int8_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<int8_t>::max() - 20);
    BigInteger integer3(std::numeric_limits<int8_t>::min());
    BigInteger integer4(std::numeric_limits<int8_t>::min() - 20);
    BigInteger integer5(std::numeric_limits<int8_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);

    auto converted = (int8_t) integer;
    auto converted1 = (int8_t) integer2;
    auto converted2 = (int8_t) integer3;
    auto converted3 = (int8_t) integer5;
    auto converted4 = (int8_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<int8_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<int8_t>::max() - 20);
    EXPECT_EQ(converted2,std::numeric_limits<int8_t>::min());
    EXPECT_EQ(converted3,std::numeric_limits<int8_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((int8_t) integer1, ConversionFailedException);
    ASSERT_THROW((int8_t) integer4, ConversionFailedException);
    ASSERT_THROW((int8_t) integer7, ConversionFailedException);
    ASSERT_THROW((int8_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, Int16ConversionTest) {
    BigInteger integer(std::numeric_limits<int16_t>::max());
    BigInteger integer1(std::numeric_limits<int16_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<int16_t>::max() - 20);
    BigInteger integer3(std::numeric_limits<int16_t>::min());
    BigInteger integer4(std::numeric_limits<int16_t>::min() - 20);
    BigInteger integer5(std::numeric_limits<int16_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);
    
    auto converted = (int16_t) integer;
    auto converted1 = (int16_t) integer2;
    auto converted2 = (int16_t) integer3;
    auto converted3 = (int16_t) integer5;
    auto converted4 = (int16_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<int16_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<int16_t>::max() - 20);
    EXPECT_EQ(converted2,std::numeric_limits<int16_t>::min());
    EXPECT_EQ(converted3,std::numeric_limits<int16_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((int16_t) integer1, ConversionFailedException);
    ASSERT_THROW((int16_t) integer4, ConversionFailedException);
    ASSERT_THROW((int16_t) integer7, ConversionFailedException);
    ASSERT_THROW((int16_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, Int32ConversionTest) {
    BigInteger integer(std::numeric_limits<int32_t>::max());
    BigInteger integer1(std::numeric_limits<int32_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<int32_t>::max() - 20);
    BigInteger integer3(std::numeric_limits<int32_t>::min());
    BigInteger integer4(std::numeric_limits<int32_t>::min() - 20);
    BigInteger integer5(std::numeric_limits<int32_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);
    
    auto converted = (int32_t) integer;
    auto converted1 = (int32_t) integer2;
    auto converted2 = (int32_t) integer3;
    auto converted3 = (int32_t) integer5;
    auto converted4 = (int32_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<int32_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<int32_t>::max() - 20);
    EXPECT_EQ(converted2,std::numeric_limits<int32_t>::min());
    EXPECT_EQ(converted3,std::numeric_limits<int32_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((int32_t) integer1, ConversionFailedException);
    ASSERT_THROW((int32_t) integer4, ConversionFailedException);
    ASSERT_THROW((int32_t) integer7, ConversionFailedException);
    ASSERT_THROW((int32_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, Int64ConversionTest) {
    BigInteger integer(std::numeric_limits<int64_t>::max());
    BigInteger integer1(std::numeric_limits<int64_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<int64_t>::max() - 20);
    BigInteger integer3(std::numeric_limits<int64_t>::min());
    BigInteger integer5(std::numeric_limits<int64_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);
    
    auto converted = (int64_t) integer;
    auto converted1 = (int64_t) integer2;
    auto converted2 = (int64_t) integer3;
    auto converted3 = (int64_t) integer5;
    auto converted4 = (int64_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<int64_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<int64_t>::max() - 20);
    EXPECT_EQ(converted2,std::numeric_limits<int64_t>::min());
    EXPECT_EQ(converted3,std::numeric_limits<int64_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((int64_t) integer1, ConversionFailedException);
    ASSERT_THROW((int64_t) integer7, ConversionFailedException);
    ASSERT_THROW((int64_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, UInt8ConversionTest) {
    BigInteger integer(std::numeric_limits<uint8_t>::max());
    BigInteger integer1(std::numeric_limits<uint8_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<uint8_t>::max() - 20);
    BigInteger integer5(std::numeric_limits<uint8_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);

    auto converted = (uint8_t) integer;
    auto converted1 = (uint8_t) integer2;
    auto converted3 = (uint8_t) integer5;
    auto converted4 = (uint8_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<uint8_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<uint8_t>::max() - 20);
    EXPECT_EQ(converted3,std::numeric_limits<uint8_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((uint8_t) integer1, ConversionFailedException);
    ASSERT_THROW((uint8_t) integer7, ConversionFailedException);
    ASSERT_THROW((uint8_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, UInt16ConversionTest) {
    BigInteger integer(std::numeric_limits<uint16_t>::max());
    BigInteger integer1(std::numeric_limits<uint16_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<uint16_t>::max() - 20);
    BigInteger integer5(std::numeric_limits<uint16_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);
    
    auto converted = (uint16_t) integer;
    auto converted1 = (uint16_t) integer2;
    auto converted3 = (uint16_t) integer5;
    auto converted4 = (uint16_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<uint16_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<uint16_t>::max() - 20);
    EXPECT_EQ(converted3,std::numeric_limits<uint16_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((uint16_t) integer1, ConversionFailedException);
    ASSERT_THROW((uint16_t) integer7, ConversionFailedException);
    ASSERT_THROW((uint16_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, UInt32ConversionTest) {
    BigInteger integer(std::numeric_limits<uint32_t>::max());
    BigInteger integer1(std::numeric_limits<uint32_t>::max() + 20);
    BigInteger integer2(std::numeric_limits<uint32_t>::max() - 20);
    BigInteger integer5(std::numeric_limits<uint32_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);

    auto converted = (uint32_t) integer;
    auto converted1 = (uint32_t) integer2;
    auto converted3 = (uint32_t) integer5;
    auto converted4 = (uint32_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<uint32_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<uint32_t>::max() - 20);
    EXPECT_EQ(converted3,std::numeric_limits<uint32_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((uint32_t) integer1, ConversionFailedException);
    ASSERT_THROW((uint32_t) integer7, ConversionFailedException);
    ASSERT_THROW((uint32_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, UInt64ConversionTest) {
    BigInteger integer(std::numeric_limits<uint64_t>::max());
    BigInteger integer2(std::numeric_limits<uint64_t>::max() - 20);
    BigInteger integer5(std::numeric_limits<uint64_t>::min() + 20);
    BigInteger integer6(0);
    BigInteger integer7("632847683274673264832648732648736284763278462837468273",10);
    BigInteger integer8("-632847683274673264832648732648736284763278462837468273",10);
    
    auto converted = (uint64_t) integer;
    auto converted1 = (uint64_t) integer2;
    auto converted3 = (uint64_t) integer5;
    auto converted4 = (uint64_t) integer6;

    EXPECT_EQ(converted,std::numeric_limits<uint64_t>::max());
    EXPECT_EQ(converted1,std::numeric_limits<uint64_t>::max() - 20);
    EXPECT_EQ(converted3,std::numeric_limits<uint64_t>::min() + 20);
    EXPECT_EQ(converted4,0);

    ASSERT_THROW((uint64_t) integer7, ConversionFailedException);
    ASSERT_THROW((uint64_t) integer8, ConversionFailedException);
}

TEST(ConversionTestSuite, StringConversionTest) {
    BigInteger integer("4672",10);
    BigInteger integer1("-4672",10);
    BigInteger integer2("4646835673486583465734865834756347856347872",10);
    BigInteger integer3("-4646835673486583465734865834756347856347872",10);

    EXPECT_EQ((std::string) integer, "4672");
    EXPECT_EQ((std::string) integer1, "-4672");
    EXPECT_EQ((std::string) integer2, "4646835673486583465734865834756347856347872");
    EXPECT_EQ((std::string) integer3, "-4646835673486583465734865834756347856347872");
}