#include "gtest/gtest.h"
#include "../ExpressionParser.hh"
#include "../ArithmeticPointerWrapper.hh"

TEST(ParserTestSuite, First)
{
    using namespace MC::FN;

    std::string input = "5x + (y + 7) * (x ^ 7) / (5y * (y + 9))";
    ArithmeticPointerWrapper result = ExpressionParser::parse(input);
    ASSERT_EQ(result->print(), "5x + (y + 7) * (x ^ 7) / (5y * (y + 9))");
}

TEST(ParserTestSuite, Second)
{
    using namespace MC::FN;
    std::string input = "x + y + x + 2 + x";
    ArithmeticPointerWrapper result = ExpressionParser::parse(input);
    ASSERT_EQ(result->print(), "y + 3x + 2");
}

TEST(ParserTestSuite, Third)
{
    using namespace MC::FN;
    std::string input = "(x + 7) * (y ^ 8) / x + 15";
    ArithmeticPointerWrapper result = ExpressionParser::parse(input);
    ASSERT_EQ(result->print(), "7(y ^ 8) / x + 15 + (y ^ 8)");
}

TEST(ParserTestSuite, Fourth)
{
    using namespace MC::FN;
    std::string input = "(5x + y ^ 8 + 19)                  ";
    ArithmeticPointerWrapper result = ExpressionParser::parse(input);
    ASSERT_EQ(result->print(), "5x + 19 + y ^ 8");
}