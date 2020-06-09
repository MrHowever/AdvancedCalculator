//
// Created by mrhowever on 27.02.2020.
//

#ifndef FUNCTIONS_ARITHMETICOBJECT_TCC
#define FUNCTIONS_ARITHMETICOBJECT_TCC

#include "ArithmeticObject.hh"

namespace MC::FN
{
    template<typename T>
    [[nodiscard]] bool containersEqual(const T& l1, const T& l2)
    {
        if(l1.size() != l2.size())
            return false;

        for(auto it = l1.begin(), it2 = l2.begin(); it != l1.end(); it++, it2++) {
            if(*it != *it2)
                return false;
        }

        return true;
    }

    template<typename T>
    void ArithmeticObject::__printList(std::string& output, const T& list, char separator, bool parentheses) const
    {
        std::string result;

        for(auto& elem : list) {
            if(parentheses)
                result += "(" + elem.print() + ")";
            else
                result += elem.print();


            if(elem != list.back())
                result += " " + std::string(1,separator) + " ";
        }

        __appendIf(output,result,separator);
    }

    template<typename T>
    void safeAssign(T** ptr, T* newValuePtr)
    {
        T* tmp = *ptr;
        *ptr = newValuePtr;
        delete(tmp);
    }
}

#endif //FUNCTIONS_ARITHMETICOBJECT_TCC
