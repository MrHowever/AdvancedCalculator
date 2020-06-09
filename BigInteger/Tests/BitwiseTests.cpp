//
// Created by mrhowever on 22.10.19.
//

#include "gtest/gtest.h"
#include "../BigInteger.hh"

TEST(BitwiseTestsSuite, IntAndTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    BigInteger result(integer1 & integer2);

    ASSERT_EQ(result._digits[0],2743578910271787014);
    ASSERT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, IntOrTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    BigInteger result = integer1 | integer2;

    ASSERT_EQ(result._digits[0],13726945275927264662);
    ASSERT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, IntXorTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    BigInteger result = integer1 ^ integer2;

    ASSERT_EQ(result._digits[0],10983366365655477648);
    ASSERT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, IntAndAssignTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    integer1 &= integer2;

    ASSERT_EQ(integer1._digits[0],2743578910271787014);
    ASSERT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, IntOrAssignTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    integer1 |= integer2;

    ASSERT_EQ(integer1._digits[0],13726945275927264662);
    ASSERT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, IntXorAssignTest) {
    BigInteger integer1;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    uint64_t integer2 = 0xAE1367FFBACED106;

    integer1 ^= integer2;

    ASSERT_EQ(integer1._digits[0],10983366365655477648);
    ASSERT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, SmallIntLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 20;
    BigInteger result(integer1 << integer2);

    EXPECT_EQ(result.toString(),"3288659249240182022242114019312634333737319517322461839360");
}

TEST(BitwiseTestsSuite, ZeroLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 0;
    BigInteger result = integer1 << integer2;

    EXPECT_EQ(result.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, SmallIntRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 20;
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"5888221818101246262738343319573566266811946232889618");
}

TEST(BitwiseTestsSuite, ZeroRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 0;
    BigInteger result(integer1 >> integer2);

    EXPECT_EQ(result.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, OneCellLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 64;
    BigInteger result(integer1 << integer2);

    EXPECT_EQ(result.toString(),"4681455603532927830628216850085429301125450909410069053440");
}

TEST(BitwiseTestsSuite, OneCellIntRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 64;
    BigInteger result(integer1 >> integer2);

    EXPECT_EQ(result.toString(),"334706659151677641985903808266219031498");
}

TEST(BitwiseTestsSuite, BiggerThanNumberLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 200;
    BigInteger result = integer1 << integer2;

    EXPECT_EQ(result.toString(),"0");
    EXPECT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, BiggerThanNumberRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 200;
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"0");
    EXPECT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, SmallIntLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 20;
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"3288659249240182022242114019312634333737319517322461839360");
}

TEST(BitwiseTestsSuite, ZeroLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 0;
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, SmallIntRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 20;
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"5888221818101246262738343319573566266811946232889618");
}

TEST(BitwiseTestsSuite, ZeroRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 0;
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, OneCellLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 64;
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"4681455603532927830628216850085429301125450909410069053440");
}

TEST(BitwiseTestsSuite, OneCellIntRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 64;
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"334706659151677641985903808266219031498");
}

TEST(BitwiseTestsSuite, BiggerThanNumberLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 200;
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"0");
    EXPECT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, BiggerThanNumberRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    uint64_t integer2 = 200;
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"0");
    EXPECT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, BigIntLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(20);
    BigInteger result(integer1 << integer2);

    EXPECT_EQ(result.toString(),"3288659249240182022242114019312634333737319517322461839360");
}

TEST(BitwiseTestsSuite, BigZeroLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(0);
    BigInteger result = integer1 << integer2;

    EXPECT_EQ(result.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, BigIntRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(20);
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"5888221818101246262738343319573566266811946232889618");
}

TEST(BitwiseTestsSuite, BigZeroRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(0);
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, OneCellBigIntLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(64);
    BigInteger result = integer1 << integer2;

    EXPECT_EQ(result.toString(),"4681455603532927830628216850085429301125450909410069053440");
}

TEST(BitwiseTestsSuite, OneCellBigIntRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(64);
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"334706659151677641985903808266219031498");
}

TEST(BitwiseTestsSuite, BiggerThanNumberBigIntLeftShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(200);
    BigInteger result = integer1 << integer2;

    EXPECT_EQ(result.toString(),"0");
    EXPECT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, BiggerThanNumberBigIntRightShiftTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(200);
    BigInteger result = integer1 >> integer2;

    EXPECT_EQ(result.toString(),"0");
    EXPECT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, BigIntLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(20);
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"3288659249240182022242114019312634333737319517322461839360");
}

TEST(BitwiseTestsSuite, BigZeroLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(0);
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, BigIntRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(20);
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"5888221818101246262738343319573566266811946232889618");
}

TEST(BitwiseTestsSuite, BigZeroRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(0);
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"6174248081137332401197121084665171821788603333098464712959");
}

TEST(BitwiseTestsSuite, OneCellBigIntLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(64);
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"4681455603532927830628216850085429301125450909410069053440");
}

TEST(BitwiseTestsSuite, OneCellBigIntRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(64);
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"334706659151677641985903808266219031498");
}

TEST(BitwiseTestsSuite, BiggerThanNumberBigLeftShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(200);
    integer1 <<= integer2;

    EXPECT_EQ(integer1.toString(),"0");
    EXPECT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, BiggerThanNumberBigRightShiftAssignTest) {
    BigInteger integer1("6174248081137332401197121084665171821788603333098464712959",10);
    BigInteger integer2(200);
    integer1 >>= integer2;

    EXPECT_EQ(integer1.toString(),"0");
    EXPECT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, BigEqualSizeOrTest) {
    BigInteger integer1;
    BigInteger integer2;
    
    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);
    
    BigInteger result(integer1 | integer2);
    
    ASSERT_EQ(result._digits[0], integer1._digits[0] | integer2._digits[0]);
    ASSERT_EQ(result._digits[1], integer1._digits[1] | integer2._digits[1]);
    ASSERT_EQ(result._digits[2], integer1._digits[2] | integer2._digits[2]);
}

TEST(BitwiseTestsSuite, BigDiffSizeOrTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    BigInteger result(integer1 | integer2);

    ASSERT_EQ(result._digits[0], integer1._digits[0] | integer2._digits[0]);
    ASSERT_EQ(result._digits[1], integer1._digits[1] | 0);
    ASSERT_EQ(result._digits[2], integer1._digits[2] | 0);
}

TEST(BitwiseTestsSuite, BigEqualSizeAndTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);

    BigInteger result(integer1 & integer2);

    ASSERT_EQ(result._digits[0], integer1._digits[0] & integer2._digits[0]);
    ASSERT_EQ(result._digits[1], integer1._digits[1] & integer2._digits[1]);
    ASSERT_EQ(result._digits[2], integer1._digits[2] & integer2._digits[2]);
}

TEST(BitwiseTestsSuite, BigDiffSizeAndTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    BigInteger result(integer1 & integer2);

    ASSERT_EQ(result._digits[0], integer1._digits[0] & integer2._digits[0]);
    ASSERT_EQ(result._digits.size(),1);
}

TEST(BitwiseTestsSuite, BigEqualSizeXorTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);

    BigInteger result(integer1 ^ integer2);

    ASSERT_EQ(result._digits[0], integer1._digits[0] ^ integer2._digits[0]);
    ASSERT_EQ(result._digits[1], integer1._digits[1] ^ integer2._digits[1]);
    ASSERT_EQ(result._digits[2], integer1._digits[2] ^ integer2._digits[2]);
}

TEST(BitwiseTestsSuite, BigDiffSizeXorTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    BigInteger result(integer1 ^ integer2);

    ASSERT_EQ(result._digits[0], integer1._digits[0] ^ integer2._digits[0]);
    ASSERT_EQ(result._digits[1], integer1._digits[1]);
    ASSERT_EQ(result._digits[2], integer1._digits[2]);
}

TEST(BitwiseTestsSuite, BigEqualSizeAssignOrTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);

    integer1 |= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 | 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits[1], 0x72FBAC4738BBCF01 | 0xF43267FABBCEEDD1);
    ASSERT_EQ(integer1._digits[2], 0x4AFFBC600126DEED | 0xF432687FEDAA001C);
}

TEST(BitwiseTestsSuite, BigDiffSizeAssignOrTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer1 |= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 | 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits[1], 0x72FBAC4738BBCF01 | 0);
    ASSERT_EQ(integer1._digits[2], 0x4AFFBC600126DEED | 0);
}

TEST(BitwiseTestsSuite, BigEqualSizeAssignAndTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);

    integer1 &= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 & 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits[1], 0x72FBAC4738BBCF01 & 0xF43267FABBCEEDD1);
    ASSERT_EQ(integer1._digits[2], 0x4AFFBC600126DEED & 0xF432687FEDAA001C);
}

TEST(BitwiseTestsSuite, BigDiffSizeAssignAndTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer1 &= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 & 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits.size(),1);
}

TEST(BitwiseTestsSuite, BigEqualSizeAssignXorTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer2._digits.push_back(0xF43267FABBCEEDD1);
    integer2._digits.push_back(0xF432687FEDAA001C);

    integer1 ^= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 ^ 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits[1], 0x72FBAC4738BBCF01 ^ 0xF43267FABBCEEDD1);
    ASSERT_EQ(integer1._digits[2], 0x4AFFBC600126DEED ^ 0xF432687FEDAA001C);
}

TEST(BitwiseTestsSuite, BigDiffSizeAssignXorTest) {
    BigInteger integer1;
    BigInteger integer2;

    integer1._digits[0] = 0x367FA67BDC10FC96;
    integer1._digits.push_back(0x72FBAC4738BBCF01);
    integer1._digits.push_back(0x4AFFBC600126DEED);

    integer2._digits[0] = 0x37245FCBBBEA32FA;
    integer1 ^= integer2;

    ASSERT_EQ(integer1._digits[0], 0x367FA67BDC10FC96 ^ 0x37245FCBBBEA32FA);
    ASSERT_EQ(integer1._digits[1], 0x72FBAC4738BBCF01);
    ASSERT_EQ(integer1._digits[2], 0x4AFFBC600126DEED);
}

TEST(BitwiseTestsSuite, NegationTest) {
    BigInteger integer;

    integer._digits[0] = 0x367FA67BDC10FC96;
    integer._digits.push_back(0x72FBAC4738BBCF01);
    integer._digits.push_back(0x4AFFBC600126DEED);

    BigInteger integer1(~integer);

    ASSERT_EQ(integer1._digits[0], ~0x367FA67BDC10FC96);
    ASSERT_EQ(integer1._digits[1], ~0x72FBAC4738BBCF01);
    ASSERT_EQ(integer1._digits[2], ~0x4AFFBC600126DEED);
}