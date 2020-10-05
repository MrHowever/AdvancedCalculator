#ifndef FUNCTIONS_TYPEDEFS_HH
#define FUNCTIONS_TYPEDEFS_HH

#include "type_traits"

namespace MC::FN
{
    class AssociativeOperator;
    class NonAssociativeOperator;
    class Value;
    class ArithmeticObject;
    template<typename T> class PointerWrapper;
    typedef PointerWrapper<ArithmeticObject> ArithmeticPointerWrapper;

    template<typename T>
    concept IsPointerWrapper = std::is_same_v<T, PointerWrapper<ArithmeticObject>>;

    template<typename T>
    concept Arithmetic = std::is_base_of_v<ArithmeticObject,T> or (std::is_convertible_v<ArithmeticPointerWrapper,T> and std::is_class_v<T>);

    template<typename T>
    concept ArithmeticRef = std::is_base_of_v<ArithmeticObject,T> and not (std::is_pointer_v<T>) and not IsPointerWrapper<T>;

    template<typename T>
    concept ArithmeticOperator = (std::is_base_of_v<ArithmeticObject,T> or std::is_convertible_v<ArithmeticPointerWrapper,T>) and !std::is_same_v<T,Value>;

    template<typename T>
    concept Primitive = std::is_arithmetic_v<T>;

    template<typename T>
    concept AssociativeRef = std::is_base_of_v<AssociativeOperator,T> and not (std::is_pointer_v<T>) and not IsPointerWrapper<T>;

    template<typename T>
    concept NonAssociativeRef = std::is_base_of_v<NonAssociativeOperator,T> and not (std::is_pointer_v<T>) and not IsPointerWrapper<T>;

    template<typename T>
    concept NotAssociativeRef = (std::is_base_of_v<ArithmeticObject, T> or std::is_base_of_v<NonAssociativeOperator,T>) and not std::is_base_of_v<AssociativeOperator,T> and not (std::is_pointer_v<T>) and not IsPointerWrapper<T>;

//    template<typename T> T Max = std::numeric_limits<T>::max();
//    template<typename T> T Min = std::numeric_limits<T>::min();
//    template<typename ...Types> using Range = MC::BO::Range<Types...>;
//
//    static const Range<float,float>             floatRange     (Min<float>,       Max<float>);
//    static const Range<double,double>           doubleRange    (Min<double>,      Max<double>);
//    static const Range<long double,long double> longDoubleRange(Min<long double>, Max<long double>);
//    static const Range<int8_t,int8_t>           int8Range      (Min<int8_t>,      Max<int8_t>);
//    static const Range<int16_t,int16_t>         int16Range     (Min<int16_t>,     Max<int16_t>);
//    static const Range<int32_t,int32_t>         int32Range     (Min<int32_t>,     Max<int32_t>);
//    static const Range<int64_t,int64_t>         int64Range     (Min<int64_t>,     Max<int64_t>);
//    static const Range<uint8_t,uint8_t>         uint8Range     (Min<uint8_t>,     Max<uint8_t>);
//    static const Range<uint16_t,uint16_t>       uint16Range    (Min<uint16_t>,    Max<uint16_t>);
//    static const Range<uint32_t,uint32_t>       uint32Range    (Min<uint32_t>,    Max<uint32_t>);
//    static const Range<uint64_t,uint64_t>       uint64Range    (Min<uint64_t>,    Max<uint64_t>);
}

#endif //FUNCTIONS_TYPEDEFS_HH
