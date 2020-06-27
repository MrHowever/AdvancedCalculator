//
// Created by mrhowever on 30.01.2020.
//

#ifndef FUNCTIONS_TYPEDEFS_HH
#define FUNCTIONS_TYPEDEFS_HH

#include <type_traits>
#include <limits>

namespace MC::FN
{
    class ArithmeticObject;
    class Sum;
    class Multiplication;
    class Division;
    class Variable;
    class Logarithm;
    class Value;

    template<bool B, class T = void> using EnableIf = std::enable_if_t<B,int>;

    template<template<class> typename T, typename ...Types> inline constexpr bool SomeOf = std::disjunction_v<T<Types>...>;
    template<template<class> typename T, typename ...Types> inline constexpr bool AllOf  = std::conjunction_v<T<Types>...>;
    template<template<class> typename T, typename ...Types> inline constexpr bool NoneOf = std::negation_v<AllOf<T<Types>...>>;

    template<typename T> inline constexpr bool IsPrimitiveV = std::is_arithmetic_v<T>;

    template<typename T> struct is_arithmetic_ptr : std::false_type {};
    template<> struct is_arithmetic_ptr<Sum*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Multiplication*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Division*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Value*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Variable*> : std::true_type {};
    template<> struct is_arithmetic_ptr<ArithmeticObject*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Logarithm*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Sum*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Multiplication*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Division*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Value*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Variable*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const ArithmeticObject*> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Logarithm*> : std::true_type {};
    template<> struct is_arithmetic_ptr<Sum* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Multiplication* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Division* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Value* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Variable* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<ArithmeticObject* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Logarithm* const> : std::true_type {};
    template<> struct is_arithmetic_ptr<Sum* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<Multiplication* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<Division* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<Value* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<Variable* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<ArithmeticObject* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<Logarithm* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Sum* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Multiplication* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Division* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Value* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Variable* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const ArithmeticObject* const&> : std::true_type {};
    template<> struct is_arithmetic_ptr<const Logarithm* const&> : std::true_type {};

    template<typename T> inline constexpr bool IsArithmeticPtrV = is_arithmetic_ptr<T>::value;
    template<typename T, typename P> inline constexpr bool AreSameV = std::is_same_v<T,P>;  //TODO variadic templates

    template<typename T> inline constexpr bool IsArithmeticV = std::is_base_of_v<ArithmeticObject,T>;

    template<typename T>
    concept Arithmetic = std::is_base_of_v<ArithmeticObject,T>;

    template<typename T>
    concept Primitive = std::is_arithmetic_v<T>;

    template<typename T> using EnableIfPrimitive = EnableIf<IsPrimitiveV<T>>;
    template<typename T> using EnableIfIsArithmetic = EnableIf<IsArithmeticV<T>>;
    template<typename T, typename P> using EnableIfAreArithmetic = EnableIf<IsArithmeticV<T> and IsArithmeticV<P>>;
    template<typename T, typename P> using EnableIfAreArithmeticOrPtr = EnableIf<(IsArithmeticV<T> or IsArithmeticV<std::remove_pointer<T>::type()>)
                                                    and (IsArithmeticV<P> or IsArithmeticV<std::remove_pointer<P>::type()>)>;

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
