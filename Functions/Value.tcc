#ifndef FUNCTIONS_VALUE_TCC
#define FUNCTIONS_VALUE_TCC

#include "InvalidOperationException.hh"
#include <cmath>
#include "Value.hh"
#include "ArithmeticPointerWrapper.hh"
#include "Multiplication.hh"
#include "Exponentiation.hh"


#define PRIMITIVE_FUNC(OP, FUNC)                                 \
    template<Primitive T>                                \
    void Value::operator OP(const T& val)               \
    {                                                   \
        switch(_current)                                \
        {                                               \
            case FLOAT:     *this = FUNC (_data.f, val); break;    \
            case DOUBLE:    *this = FUNC (_data.d  , val); break;    \
            case LDOUBLE:   *this = FUNC (_data.ld , val); break;    \
            case INT8:      *this = FUNC (_data.i8 , val); break;    \
            case INT16:     *this = FUNC (_data.i16, val); break;    \
            case INT32:     *this = FUNC (_data.i32, val); break;    \
            case INT64:     *this = FUNC (_data.i64, val); break;    \
            case UINT8:     *this = FUNC (_data.u8 , val); break;    \
            case UINT16:    *this = FUNC (_data.u16, val); break;    \
            case UINT32:    *this = FUNC (_data.u32, val); break;    \
            case UINT64:    *this = FUNC (_data.u64, val); break;    \
       default: throw InvalidOperationException("Implementation error"); \
        }                                               \
    }

namespace MC::FN
{
    template<Primitive T>
    Value::Value(T) : Value()
    {
        throw InvalidOperationException("This type cannot be assigned to Value object");
    }

    template<Primitive T>
    Value& Value::operator=(T val)
    {
        throw InvalidOperationException("This type cannot be assigned to Value object");
    }


#define PRIMITIVE_ASSIGN_OP(OP)                                 \
    template<Primitive T>                                \
    void Value::operator OP##= (const T& val)               \
    {                                                   \
        switch(_current)                                \
        {                                               \
            case FLOAT:     *this = _data.f   OP val; break;    \
            case DOUBLE:    *this = _data.d   OP val; break;    \
            case LDOUBLE:   *this = _data.ld  OP val; break;    \
            case INT8:      *this = _data.i8  OP val; break;    \
            case INT16:     *this = _data.i16 OP val; break;    \
            case INT32:     *this = _data.i32 OP val; break;    \
            case INT64:     *this = _data.i64 OP val; break;    \
            case UINT8:     *this = _data.u8  OP val; break;    \
            case UINT16:    *this = _data.u16 OP val; break;    \
            case UINT32:    *this = _data.u32 OP val; break;    \
            case UINT64:    *this = _data.u64 OP val; break;    \
            default: throw InvalidOperationException("Implementation error"); \
        }                                               \
    }
    
    PRIMITIVE_ASSIGN_OP(+)
    PRIMITIVE_ASSIGN_OP(*)
    PRIMITIVE_ASSIGN_OP(/)
    PRIMITIVE_FUNC(^=, std::pow)

    template<Primitive T>                                
    void Value::operator%=(const T& val)               
    {                                                   
        switch(_current)                                
        {
            case FLOAT:
            case DOUBLE:
            case LDOUBLE:   throw InvalidOperationException("Modulo operation on floating point values");
            case INT8:      _data.i8  %= val; break;    
            case INT16:     _data.i16 %= val; break;    
            case INT32:     _data.i32 %= val; break;    
            case INT64:     _data.i64 %= val; break;    
            case UINT8:     _data.u8  %= val; break;    
            case UINT16:    _data.u16 %= val; break;    
            case UINT32:    _data.u32 %= val; break;    
            case UINT64:    _data.u64 %= val; break;
            default: throw InvalidOperationException("Implementation error");
        }                                               
    }

#define COMPARISON_OP(OP) \
    template<Primitive T>                  \
    bool Value::operator OP (const T& second) const \
    {                                            \
        return *this OP Value(second);                 \
    }

    COMPARISON_OP(<)
    COMPARISON_OP(<=)
    COMPARISON_OP(>)
    COMPARISON_OP(>=)

#define PRIMITIVE_OP_FREE(OP) \
    template<Primitive T>                  \
    Value operator OP (const T& v1, const Value& v2) \
    {                                            \
        return Value(v1) OP v2;                 \
    }

    PRIMITIVE_OP_FREE(+)
    PRIMITIVE_OP_FREE(*)
    PRIMITIVE_OP_FREE(/)
    PRIMITIVE_OP_FREE(^)
    
    template<Primitive T>
    Value::operator T() const
    {
        switch(_current)
        {
            case Value::FLOAT:     return (T) _data.f;
            case Value::DOUBLE:    return (T) _data.d;
            case Value::LDOUBLE:   return (T) _data.ld;
            case Value::INT8:      return (T) _data.i8;
            case Value::INT16:     return (T) _data.i16;
            case Value::INT32:     return (T) _data.i32;
            case Value::INT64:     return (T) _data.i64;
            case Value::UINT8:     return (T) _data.u8;
            case Value::UINT16:    return (T) _data.u16;
            case Value::UINT32:    return (T) _data.u32;
            case Value::UINT64:    return (T) _data.u64;
            default: throw InvalidOperationException("Implementation error");
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator+(const T& o1, const P& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o1 + Value(o2));
        } else {
            return o1 + Value(o2);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator*(const T& o1, const P& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o1 * Value(o2));
        } else {
            return o1 * Value(o2);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator/(const T& o1, const P& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o1 / Value(o2));
        } else {
            return o1 / Value(o2);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator^(const T& o1, const P& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o1 ^ Value(o2));
        } else {
            return o1 ^ Value(o2);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator+(const P& o1, const T& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o2 + Value(o1));
        } else {
            return o2 + Value(o1);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator*(const P& o1, const T& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(o2 * Value(o1));
        } else {
            return o2 * Value(o1);
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator/(const P& o1, const T& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(Value(o1) / o2);
        } else {
            return Value(o1) / o2;
        }
    }

    template<Arithmetic T, Primitive P>
    ArithmeticPointerWrapper operator^(const P& o1, const T& o2)
    {
        if constexpr(std::is_same_v<T,Value>) {
            return (ValuePointerWrapper) new Value(Value(o1) ^ o2);
        } else {
            return Value(o1) ^ o2;
        }
    }
}

#endif //FUNCTIONS_VALUE_TCC
