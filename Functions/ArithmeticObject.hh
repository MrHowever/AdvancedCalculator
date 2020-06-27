//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_ARITHMETICOBJECT_HH
#define FUNCTIONS_ARITHMETICOBJECT_HH

#include "ArithmeticType.hh"
#include <string>

namespace MC::FN
{
    class Value;

    class ArithmeticObject {
    protected:
        void __appendIf(std::string&, const std::string&, char) const;
        template<typename T> void __printList(std::string&,const T&, char, bool = false) const;

    public:
        [[nodiscard]] virtual Value evaluate(const Value&) const = 0;
        [[nodiscard]] virtual std::string print() const  = 0;
        [[nodiscard]] constexpr virtual ArithmeticType getType() const = 0;

        virtual ~ArithmeticObject() = default;
    };

    std::ostream& operator<<(std::ostream&, const ArithmeticObject&);
    template<typename T> void safeAssign(T**,T*);
}

#endif //FUNCTIONS_ARITHMETICOBJECT_HH

#include "ArithmeticObject.tcc"
