#include <iostream>
#include "ArithmeticObject.hh"

namespace MC::FN
{
    std::ostream& operator<<(std::ostream& strm, const ArithmeticObject& obj)
    {
        return strm << obj.print();
    }

    void ArithmeticObject::__appendIf(std::string& output, const std::string& input, char separator) const
    {
        if(input.empty())
            return;

        !output.empty() ? output += " " + std::string(1, separator) + " " + input : output = input;
    }
}