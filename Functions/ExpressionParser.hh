//
// Created by mmm on 04.07.2020.
//

#ifndef FUNCTIONS_EXPRESSIONPARSER_HH
#define FUNCTIONS_EXPRESSIONPARSER_HH

#include <string>
#include "ArithmeticObject.hh"

namespace MC::FN
{
    class ExpressionParser {
        typedef std::string::size_type index_t;

        [[nodiscard]] static std::string preprocess(std::string);
        [[nodiscard]] static index_t middleIndex(const std::string&);
        [[nodiscard]] static index_t freeOp(std::string, char);
        [[nodiscard]] static ArithmeticPointerWrapper createObject(std::string);

        [[nodiscard]] static bool isNumber(const std::string&);
        [[nodiscard]] static bool isVariable(const std::string&);

    public:
        [[nodiscard]] static ArithmeticPointerWrapper parse(std::string);
    };
}


#endif //FUNCTIONS_EXPRESSIONPARSER_HH
