//
// Created by mrhowever on 27.02.2020.
//

#include "ArithmeticObject.hh"
#include <iostream>

namespace MC::FN
{
    std::ostream& operator<<(std::ostream& strm, const Operand& obj)
    {
        strm << obj.print();
    }

    void ArithmeticObject::__appendIf(std::string& output, const std::string& input, char separator) const
    {
        if(input.empty())
            return;

        !output.empty() ? output += " " + std::string(1, separator) + " " + input : output = input;
    }
}