//
// Created by mrhowever on 23.03.2020.
//

#ifndef FUNCTIONS_CUSTOMPOINTER_HH
#define FUNCTIONS_CUSTOMPOINTER_HH

template<typename T>
class CustomPointer {
    T* __ptr;

    explicit CustomPointer(T* oPtr) : __ptr(oPtr) {}
    T* operator*(int) { return __ptr; }
};


#endif //FUNCTIONS_CUSTOMPOINTER_HH
