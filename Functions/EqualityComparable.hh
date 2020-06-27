//
// Created by mrhowever on 21.06.2020.
//

#ifndef FUNCTIONS_EQUALITYCOMPARABLE_HH
#define FUNCTIONS_EQUALITYCOMPARABLE_HH

template<typename T>
class EqualityComparable {
public:
    [[nodiscard]] virtual bool operator==(const T&) const = 0;
    [[nodiscard]] virtual bool operator!=(const T&) const = 0;
};


#endif //FUNCTIONS_EQUALITYCOMPARABLE_HH
