#ifndef FUNCTIONS_ARITHMETICOBJECT_HH
#define FUNCTIONS_ARITHMETICOBJECT_HH

#include "ArithmeticType.hh"
#include <string>

namespace MC::FN
{
    class ArithmeticObject;
    class Value;
    template<typename T> class PointerWrapper;
    typedef PointerWrapper<ArithmeticObject> ArithmeticPointerWrapper;

    class ArithmeticObject {
    public:
        [[nodiscard]] virtual Value evaluate(const Value&) const = 0;
        [[nodiscard]] virtual std::string print() = 0;
        [[nodiscard]] constexpr virtual ArithmeticType getType() const = 0;

        virtual ~ArithmeticObject() = default;
    };

    std::ostream& operator<<(std::ostream&, ArithmeticObject&);
    std::string addBraces(const std::string&);
    [[nodiscard]] bool compare(const ArithmeticPointerWrapper&, const ArithmeticPointerWrapper&);


#define TEMPLATE_SPECIALIZATION_FIRST(FUNC) \
    template PointerWrapper<ArithmeticObject> FUNC <Sum>(const Sum&, const PointerWrapper<ArithmeticObject>&); \
    template PointerWrapper<ArithmeticObject> FUNC <Multiplication>(const Multiplication&, const PointerWrapper<ArithmeticObject>&); \
    template PointerWrapper<ArithmeticObject> FUNC <Division>(const Division&, const PointerWrapper<ArithmeticObject>&); \
    template PointerWrapper<ArithmeticObject> FUNC <Exponentiation>(const Exponentiation&, const PointerWrapper<ArithmeticObject>&); \
    template PointerWrapper<ArithmeticObject> FUNC <Variable>(const Variable&, const PointerWrapper<ArithmeticObject>&); \
    template PointerWrapper<ArithmeticObject> FUNC <Value>(const Value&, const PointerWrapper<ArithmeticObject>&); \

#define TEMPLATE_SPECIALIZATION_SECOND(FUNC) \
    template PointerWrapper<ArithmeticObject> FUNC <Sum>(const PointerWrapper<ArithmeticObject>&, const Sum&); \
    template PointerWrapper<ArithmeticObject> FUNC <Multiplication>(const PointerWrapper<ArithmeticObject>&, const Multiplication&); \
    template PointerWrapper<ArithmeticObject> FUNC <Division>(const PointerWrapper<ArithmeticObject>&, const Division&); \
    template PointerWrapper<ArithmeticObject> FUNC <Exponentiation>(const PointerWrapper<ArithmeticObject>&, const Exponentiation&); \
    template PointerWrapper<ArithmeticObject> FUNC <Variable>(const PointerWrapper<ArithmeticObject>&, const Variable&); \
    template PointerWrapper<ArithmeticObject> FUNC <Value>(const PointerWrapper<ArithmeticObject>&, const Value&); \

#define TEMPLATE_SPECIALIZATION(FUNC) \
    TEMPLATE_SPECIALIZATION_FIRST( FUNC ) \
    TEMPLATE_SPECIALIZATION_SECOND( FUNC )

}

#endif //FUNCTIONS_ARITHMETICOBJECT_HH
