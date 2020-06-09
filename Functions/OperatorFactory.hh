//
// Created by mrhowever on 24.03.2020.
//

#ifndef FUNCTIONS_OPERATORFACTORY_HH
#define FUNCTIONS_OPERATORFACTORY_HH

#include "ArithmeticObject.hh"

namespace MC::FN
{
    class OperatorFactory {
    public:
        template<typename T> static ArithmeticObject* copy(const T*);
    };
}


#endif //FUNCTIONS_OPERATORFACTORY_HH
