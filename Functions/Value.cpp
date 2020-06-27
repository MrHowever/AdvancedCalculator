//
// Created by mrhowever on 11.02.2020.
//

#include "Value.hh"

#define ASSIGNMENT_OP(TYPE,FIELD,ENUM)  \
    template<>                          \
    Value& Value::operator=(TYPE val)   \
    {                                   \
        FIELD = val;                    \
        _current = ENUM;                \
        return *this;                   \
    }

#define OP_DEFINITION(OP)                                           \
    Value Value::operator OP(const Value& second) const            \
    {                                                               \
        Value result = second;                                      \
                                                                    \
        switch(_current)                                            \
        {                                                           \
            case Value::FLOAT:     result OP##= _data.f;   break;     \
            case Value::DOUBLE:    result OP##= _data.d;   break;     \
            case Value::LDOUBLE:   result OP##= _data.ld;  break;     \
            case Value::INT8:      result OP##= _data.i8;  break;     \
            case Value::INT16:     result OP##= _data.i16; break;     \
            case Value::INT32:     result OP##= _data.i32; break;     \
            case Value::INT64:     result OP##= _data.i64; break;     \
            case Value::UINT8:     result OP##= _data.u8;  break;     \
            case Value::UINT16:    result OP##= _data.u16; break;     \
            case Value::UINT32:    result OP##= _data.u32; break;     \
            case Value::UINT64:    result OP##= _data.u64; break;     \
        }                                                           \
                                                                    \
        return result;                                              \
    }                                                               \

#define VALUE_OP(OP)                                        \
    void Value::operator OP(const Value& val)                \
    {                                                       \
        switch(val._current)                                \
        {                                                   \
            case FLOAT:     _data.f OP val._data.f;   break;  \
            case DOUBLE:    _data.d OP val._data.d;   break;  \
            case LDOUBLE:   _data.ld OP val._data.ld;  break;  \
            case INT8:      _data.i8 OP val._data.i8;  break;  \
            case INT16:     _data.i16 OP val._data.i16; break;  \
            case INT32:     _data.i32 OP val._data.i32; break;  \
            case INT64:     _data.i64 OP val._data.i64; break;  \
            case UINT8:     _data.u8 OP val._data.u8;  break;  \
            case UINT16:    _data.u16 OP val._data.u16; break;  \
            case UINT32:    _data.u32 OP val._data.u32; break;  \
            case UINT64:    _data.u64 OP val._data.u64; break;  \
       }                                                    \
    }

namespace MC::FN
{

    template<> Value::Value(float val)       :  _current(FLOAT),     _data{.f = val}   {}
    template<> Value::Value(double val)      :  _current(DOUBLE),    _data{.d = val}   {}
    template<> Value::Value(long double val) :  _current(LDOUBLE),   _data{.ld = val}  {}
    template<> Value::Value(int8_t val)      :  _current(INT8),      _data{.i8 = val}  {}
    template<> Value::Value(int16_t val)     :  _current(INT16),     _data{.i16 = val} {}
    template<> Value::Value(int32_t val)     :  _current(INT32),     _data{.i32 = val} {}
    template<> Value::Value(int64_t val)     :  _current(INT64),     _data{.i64 = val} {}
    template<> Value::Value(uint8_t val)     :  _current(UINT8),     _data{.u8 = val}  {}
    template<> Value::Value(uint16_t val)    :  _current(UINT16),    _data{.u16 = val} {}
    template<> Value::Value(uint32_t val)    :  _current(UINT32),    _data{.u32 = val} {}
    template<> Value::Value(uint64_t val)    :  _current(UINT64),    _data{.u64 = val} {}
    template<> Value::Value(bool val)        :  _current(INT32),       _data{.i32 = val} {}
//  template<> Value::Value(BigInteger val)  :  _current(BIGINT),    _data{.bi = val}  {}
//  template<> Value::Value(BigDouble val)   :  _current(BIGDOUBLE), _data{.bd = val}  {}

    ASSIGNMENT_OP(float,   _data.f,FLOAT)
    ASSIGNMENT_OP(double,  _data.d,DOUBLE)
    ASSIGNMENT_OP(long double,_data.ld,LDOUBLE)
    ASSIGNMENT_OP(int8_t,  _data.i8,INT8)
    ASSIGNMENT_OP(int16_t, _data.i16,INT16)
    ASSIGNMENT_OP(int32_t, _data.i32,INT32)
    ASSIGNMENT_OP(int64_t, _data.i64,INT64)
    ASSIGNMENT_OP(uint8_t, _data.u8,UINT8)
    ASSIGNMENT_OP(uint16_t,_data.u16,UINT16)
    ASSIGNMENT_OP(uint32_t,_data.u32,UINT32)
    ASSIGNMENT_OP(uint64_t,_data.u64,UINT64)

    //TODO add to defines too
//  ASSIGNMENT_OP(BigInteger,_data.bi,BIGINT)
//  ASSIGNMENT_OP(BigDouble,_data.bd,BIGDOUBLE)

    OP_DEFINITION(+)
    OP_DEFINITION(*)
    OP_DEFINITION(/)

    VALUE_OP(+=)
    VALUE_OP(*=)
    VALUE_OP(/=)

    Value Value::evaluate(const Value& val) const
    {
        return *this;
    }

    std::string Value::print() const
    {
        switch(_current)
        {
            case FLOAT:     return std::to_string(_data.f);
            case DOUBLE:    return std::to_string(_data.d);
            case LDOUBLE:   return std::to_string(_data.ld);
            case INT8:      return std::to_string(_data.i8);
            case INT16:     return std::to_string(_data.i16);
            case INT32:     return std::to_string(_data.i32);
            case INT64:     return std::to_string(_data.i64);
            case UINT8:     return std::to_string(_data.u8 );
            case UINT16:    return std::to_string(_data.u16);
            case UINT32:    return std::to_string(_data.u32);
            case UINT64:    return std::to_string(_data.u64);
//          case BIGINT:    return std::to_string(_data.bi);
//          case BIGDOUBLE: return std::to_string(_data.bd);

            default: throw InvalidOperationException("Type not handled");
        }
    }

//    constexpr ArithmeticType Value::getType() const
//    {
//        return VAL;
//    }

    bool Value::operator==(const Value& o) const
    {
        if (_current != o._current)
            return false;

        switch (_current) {
            case FLOAT:   return _data.f   == o._data.f;
            case DOUBLE:  return _data.d   == o._data.d;
            case LDOUBLE: return _data.ld  == o._data.ld;
            case INT8:    return _data.i8  == o._data.i8;
            case INT16:   return _data.i16 == o._data.i16;
            case INT32:   return _data.i32 == o._data.i32;
            case INT64:   return _data.i64 == o._data.i64;
            case UINT8:   return _data.u8  == o._data.u8;
            case UINT16:  return _data.u16 == o._data.u16;
            case UINT32:  return _data.u32 == o._data.u32;
            case UINT64:  return _data.u64 == o._data.u64;
//          case BIGINT:    return _data.bi == o._data.bi;
//          case BIGDOUBLE: return _data.bd == o._data.bd;
            default: throw InvalidOperationException("Type not handled");
        }
    }

    bool Value::operator!=(const Value& o) const
    {
        return !(*this == o);
    }

    bool Value::operator<(const Value& o) const
    {
        if (_current != o._current)
            return false;

        switch (_current) {
            case FLOAT:   return _data.f   < o._data.f;
            case DOUBLE:  return _data.d   < o._data.d;
            case LDOUBLE: return _data.ld  < o._data.ld;
            case INT8:    return _data.i8  < o._data.i8;
            case INT16:   return _data.i16 < o._data.i16;
            case INT32:   return _data.i32 < o._data.i32;
            case INT64:   return _data.i64 < o._data.i64;
            case UINT8:   return _data.u8  < o._data.u8;
            case UINT16:  return _data.u16 < o._data.u16;
            case UINT32:  return _data.u32 < o._data.u32;
            case UINT64:  return _data.u64 < o._data.u64;
//          case BIGINT:    return _data.bi < o._data.bi;
//          case BIGDOUBLE: return _data.bd < o._data.bd;
            default: throw InvalidOperationException("Type not handled");
        }
    }

    bool Value::operator<=(const Value& o) const
    {
        if (_current != o._current)
            return false;

        switch (_current) {
            case FLOAT:   return _data.f   <= o._data.f;
            case DOUBLE:  return _data.d   <= o._data.d;
            case LDOUBLE: return _data.ld  <= o._data.ld;
            case INT8:    return _data.i8  <= o._data.i8;
            case INT16:   return _data.i16 <= o._data.i16;
            case INT32:   return _data.i32 <= o._data.i32;
            case INT64:   return _data.i64 <= o._data.i64;
            case UINT8:   return _data.u8  <= o._data.u8;
            case UINT16:  return _data.u16 <= o._data.u16;
            case UINT32:  return _data.u32 <= o._data.u32;
            case UINT64:  return _data.u64 <= o._data.u64;
//          case BIGINT:    return _data.bi <= o._data.bi;
//          case BIGDOUBLE: return _data.bd <= o._data.bd;
            default: throw InvalidOperationException("Type not handled");
        }
    }

    bool Value::operator>(const Value& o) const
    {
        if (_current != o._current)
            return false;

        switch (_current) {
            case FLOAT:   return _data.f   > o._data.f;
            case DOUBLE:  return _data.d   > o._data.d;
            case LDOUBLE: return _data.ld  > o._data.ld;
            case INT8:    return _data.i8  > o._data.i8;
            case INT16:   return _data.i16 > o._data.i16;
            case INT32:   return _data.i32 > o._data.i32;
            case INT64:   return _data.i64 > o._data.i64;
            case UINT8:   return _data.u8  > o._data.u8;
            case UINT16:  return _data.u16 > o._data.u16;
            case UINT32:  return _data.u32 > o._data.u32;
            case UINT64:  return _data.u64 > o._data.u64;
//          case BIGINT:    return _data.bi > o._data.bi;
//          case BIGDOUBLE: return _data.bd > o._data.bd;
            default: throw InvalidOperationException("Type not handled");
        }
    }

    bool Value::operator>=(const Value& o) const
    {
        if (_current != o._current)
            return false;

        switch (_current) {
            case FLOAT:   return _data.f   >= o._data.f;
            case DOUBLE:  return _data.d   >= o._data.d;
            case LDOUBLE: return _data.ld  >= o._data.ld;
            case INT8:    return _data.i8  >= o._data.i8;
            case INT16:   return _data.i16 >= o._data.i16;
            case INT32:   return _data.i32 >= o._data.i32;
            case INT64:   return _data.i64 >= o._data.i64;
            case UINT8:   return _data.u8  >= o._data.u8;
            case UINT16:  return _data.u16 >= o._data.u16;
            case UINT32:  return _data.u32 >= o._data.u32;
            case UINT64:  return _data.u64 >= o._data.u64;
//          case BIGINT:    return _data.bi >= o._data.bi;
//          case BIGDOUBLE: return _data.bd >= o._data.bd;
            default: throw InvalidOperationException("Type not handled");
        }
    }

    Value::Value() : _data(), _current()
    {
        *this = 0;
    }

    Value& Value::operator++()
    {
        *this += 1;
        return *this;
    }

    Value Value::operator++(int)
    {
        Value copy(*this);
        operator++();
        return copy;
    }

    Value::operator bool() const
    {
        return *this != Value(0);
    }
}