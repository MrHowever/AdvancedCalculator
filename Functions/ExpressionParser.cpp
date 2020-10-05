//
// Created by mmm on 04.07.2020.
//

#include <algorithm>
#include "ExpressionParser.hh"
#include "ArithmeticPointerWrapper.hh"
#include "ExponentiationOperators.hh"

namespace MC::FN
{
    ArithmeticPointerWrapper ExpressionParser::parse(std::string in)
    {
        std::string input = preprocess(in);
        index_t middleIdx = middleIndex(input);

        if(middleIdx) {
            std::string leftOperand = input.substr(0, middleIdx);
            std::string rightOperand = input.substr(middleIdx + 1);

            ArithmeticPointerWrapper leftOp = parse(leftOperand);
            ArithmeticPointerWrapper rightOp = parse(rightOperand);

            switch (input[middleIdx]) {
                case '+':
                    return leftOp + rightOp;
                case '*':
                    return leftOp * rightOp;
                case '/':
                    return leftOp / rightOp;
                case '^':
                    return leftOp ^ rightOp;
                default:
                    throw InvalidOperationException("Unknown operator " + std::string(1,input[middleIdx]));
            }
        }
        else {
            return createObject(input);
        }
    }

    std::string ExpressionParser::preprocess(std::string in)
    {
        std::string input = std::move(in);

        // Remove whitespace
        input.erase(std::remove_if(input.begin(), input.end(), isspace), input.end());

        // If expression is inside redundant parentheses remove them
        // If first parenthesis matches last parenthesis the parentheses count should never reach 0
        if(input.front() == '(' && input.back() == ')') {
            int parenthesesCnt = 0;
            std::string::iterator it = input.begin();

            do {
                if (*it == '(') parenthesesCnt++;
                if (*it == ')') parenthesesCnt--;
                it++;
            } while(it < input.end() && parenthesesCnt);

            if(it == input.end()) {
                input.erase(input.begin());
                input.erase(input.end() - 1);
            }
        }

        return input;
    }

    ExpressionParser::index_t ExpressionParser::middleIndex(const std::string& input)
    {
        index_t idx = 0;
        const char opHierarchy[4] = {'+', '*', '/', '^'};

        for(auto& elem : opHierarchy) {
            if(input.find(elem) != std::string::npos) {
                idx = freeOp(input, elem);

                if (idx)
                    return idx;
            }
        }

        return 0;
    }

    ExpressionParser::index_t ExpressionParser::freeOp(std::string input, char op)
    {
        index_t parenthesesCnt = 0;

        for(index_t i = 0; i < input.size(); i++) {
            char elem = input[i];

            if (elem == '(')
                parenthesesCnt++;
            else if (elem == ')')
                parenthesesCnt--;
            else {
                if (!parenthesesCnt && elem == op) {
                    return i;
                }
            }
        }

        return 0;
    }

    ArithmeticPointerWrapper ExpressionParser::createObject(std::string in)
    {
        if(isNumber(in)) {
            return (ArithmeticPointerWrapper) new Value(in);
        } else if(isVariable(in)) {
            return (ArithmeticPointerWrapper) new Variable(in[0]);
        } else {
            index_t numberIdx = 0;

            while(isdigit(in[numberIdx]) || in[numberIdx] == '.' || in[numberIdx] == ',') {
                numberIdx++;
            }

            std::string factor = in.substr(0,numberIdx);
            char var = in[numberIdx];

            return Variable(var) * Value(factor);
        }
    }

    bool ExpressionParser::isNumber(const std::string& input)
    {
        return std::ranges::all_of(input, [&input](auto& e){
            return isdigit(e) || e == '.' || e == ',';
        });
    }

    bool ExpressionParser::isVariable(const std::string& input)
    {
        return input.size() == 1 and isalpha(input[0]);
    }
}