//
// Created by mrhowever on 28.01.20.
//

#ifndef FUNCTIONS_ARITHMETICOBJECT_HH
#define FUNCTIONS_ARITHMETICOBJECT_HH

#include "ArithmeticType.hh"
#include "Typedef.hh"

namespace MC::FN
{
    class Value;

    class ArithmeticObject {
    protected:
        void __appendIf(std::string&, const std::string&, char) const;
        template<typename T> void __printList(std::string&,const T&, char, bool = false) const;

    public:

        virtual void simplify() = 0;
        [[nodiscard]] virtual Value evaluate(const Value&) const = 0;
        [[nodiscard]] virtual std::string print() const  = 0;
        //TODO make constexpr when porting to C++20
        [[nodiscard]] virtual ArithmeticType getType() const = 0;

        virtual ~ArithmeticObject() = default;
    };

    std::ostream& operator<<(std::ostream&, const Operand&);
    template<typename T> [[nodiscard]] bool containersEqual(const T& l1, const T& l2);
    template<typename T> void safeAssign(T**,T*);
}

#endif //FUNCTIONS_ARITHMETICOBJECT_HH
