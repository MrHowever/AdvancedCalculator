//
// Created by mrhowever on 15.02.2020.
//

#ifndef FUNCTIONS_VALUE_TCC
#define FUNCTIONS_VALUE_TCC

#include "Typedefs.hh"
#include "InvalidOperationException.hh"
#include "Sum.hh"
#include "Multiplication.hh"
#include "Division.hh"

#define TEMPLATE_OP(OP)                                 \
    template<typename T>                                \
    void Value::operator OP(const T& val)               \
    {                                                   \
        switch(_current)                                \
        {                                               \
            case FLOAT:     _data.f   OP val; break;    \
            case DOUBLE:    _data.d   OP val; break;    \
            case LDOUBLE:   _data.ld  OP val; break;    \
            case INT8:      _data.i8  OP val; break;    \
            case INT16:     _data.i16 OP val; break;    \
            case INT32:     _data.i32 OP val; break;    \
            case INT64:     _data.i64 OP val; break;    \
            case UINT8:     _data.u8  OP val; break;    \
            case UINT16:    _data.u16 OP val; break;    \
            case UINT32:    _data.u32 OP val; break;    \
            case UINT64:    _data.u64 OP val; break;    \
        }                                               \
    }

namespace MC::FN
{
    template<typename T>
    Value::Value(T) :  _data(), _current()
    {
        throw InvalidOperationException("This type cannot be assigned to Value object");
    }

    template<typename T>
    Value& Value::operator=(T val)
    {
        throw InvalidOperationException("This type cannot be assigned to Value object");
    }

    TEMPLATE_OP(+=)
    TEMPLATE_OP(*=)
    TEMPLATE_OP(/=)

    template<typename T>
    bool Value::operator<(const T& o) const
    {
        return *this < Value(o);
    }

    template<typename T>
    bool Value::operator<=(const T& o) const
    {
        return *this <= Value(o);
    }

    template<typename T>
    bool Value::operator>(const T& o) const
    {
        return *this > Value(o);
    }

    template<typename T>
    bool Value::operator>=(const T& o) const
    {
        return *this >= Value(o);
    }
}

#endif //FUNCTIONS_VALUE_TCC
