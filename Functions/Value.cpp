#include "Value.hh"
#include <cmath>
#include <algorithm>
#include "ArithmeticPointerWrapper.hh"
#include <sstream>

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


#define ASSIGNMENT_OP(TYPE,FIELD,ENUM)  \
    template<>                          \
    Value& Value::operator=(TYPE val)   \
    {                                   \
        FIELD = val;                    \
        _current = ENUM;                \
        return *this;                   \
    }

    ASSIGNMENT_OP(float,   _data.f,   FLOAT)
    ASSIGNMENT_OP(double,  _data.d,   DOUBLE)
    ASSIGNMENT_OP(long double,_data.ld, LDOUBLE)
    ASSIGNMENT_OP(int8_t,  _data.i8,  INT8)
    ASSIGNMENT_OP(int16_t, _data.i16, INT16)
    ASSIGNMENT_OP(int32_t, _data.i32, INT32)
    ASSIGNMENT_OP(int64_t, _data.i64, INT64)
    ASSIGNMENT_OP(uint8_t, _data.u8,  UINT8)
    ASSIGNMENT_OP(uint16_t,_data.u16, UINT16)
    ASSIGNMENT_OP(uint32_t,_data.u32, UINT32)
    ASSIGNMENT_OP(uint64_t,_data.u64, UINT64)

    //TODO add to defines too
//  ASSIGNMENT_OP(BigInteger,_data.bi,BIGINT)
//  ASSIGNMENT_OP(BigDouble,_data.bd,BIGDOUBLE)


#define CALL_OP(VALUE, OP)                                             \
   switch(_current)                                            \
        {                                                           \
            case Value::FLOAT:     return Value(_data.f   OP VALUE); \
            case Value::DOUBLE:    return Value(_data.d   OP VALUE); \
            case Value::LDOUBLE:   return Value(_data.ld  OP VALUE); \
            case Value::INT8:      return Value(_data.i8  OP VALUE); \
            case Value::INT16:     return Value(_data.i16 OP VALUE); \
            case Value::INT32:     return Value(_data.i32 OP VALUE); \
            case Value::INT64:     return Value(_data.i64 OP VALUE); \
            case Value::UINT8:     return Value(_data.u8  OP VALUE); \
            case Value::UINT16:    return Value(_data.u16 OP VALUE); \
            case Value::UINT32:    return Value(_data.u32 OP VALUE); \
            case Value::UINT64:    return Value(_data.u64 OP VALUE); \
            default: throw InvalidOperationException("Implementation error5"); \
        }

#define OP_DEFINITION(OP)                                           \
    Value Value::operator OP(const Value& second) const            \
    {                                                               \
        switch(second._current)                                           \
        {                                                                 \
            case Value::FLOAT:     CALL_OP(second._data.f, OP);    \
            case Value::DOUBLE:    CALL_OP(second._data.d, OP);    \
            case Value::LDOUBLE:   CALL_OP(second._data.ld, OP);   \
            case Value::INT8:      CALL_OP(second._data.i8, OP);   \
            case Value::INT16:     CALL_OP(second._data.i16, OP);  \
            case Value::INT32:     CALL_OP(second._data.i32, OP);  \
            case Value::INT64:     CALL_OP(second._data.i64, OP);  \
            case Value::UINT8:     CALL_OP(second._data.u8, OP);   \
            case Value::UINT16:    CALL_OP(second._data.u16, OP);  \
            case Value::UINT32:    CALL_OP(second._data.u32, OP);  \
            case Value::UINT64:    CALL_OP(second._data.u64, OP); \
            default: throw InvalidOperationException("Implementation error6"); \
        }                                                                 \
    }

    OP_DEFINITION(+)
    OP_DEFINITION(*)


#define CALL_FUNC(VALUE, FUNC)                                             \
   switch(_current)                                            \
        {                                                           \
            case Value::FLOAT:     return Value( FUNC (_data.f,   VALUE )); \
            case Value::DOUBLE:    return Value( FUNC (_data.d,   VALUE )); \
            case Value::LDOUBLE:   return Value( FUNC (_data.ld,  VALUE )); \
            case Value::INT8:      return Value( FUNC (_data.i8,  VALUE )); \
            case Value::INT16:     return Value( FUNC (_data.i16, VALUE )); \
            case Value::INT32:     return Value( FUNC (_data.i32, VALUE )); \
            case Value::INT64:     return Value( FUNC (_data.i64, VALUE )); \
            case Value::UINT8:     return Value( FUNC (_data.u8,  VALUE )); \
            case Value::UINT16:    return Value( FUNC (_data.u16, VALUE )); \
            case Value::UINT32:    return Value( FUNC (_data.u32, VALUE )); \
            case Value::UINT64:    return Value( FUNC (_data.u64, VALUE )); \
            default: throw InvalidOperationException("Implementation error7"); \
        }

#define FUNC_DEFINITION(OP, FUNC)                                           \
    Value Value::operator OP(const Value& second) const            \
    {                                                               \
        switch(second._current)                                               \
        {                                                                     \
            case Value::FLOAT:     CALL_FUNC(second._data.f,   FUNC); \
            case Value::DOUBLE:    CALL_FUNC(second._data.d,   FUNC); \
            case Value::LDOUBLE:   CALL_FUNC(second._data.ld,  FUNC); \
            case Value::INT8:      CALL_FUNC(second._data.i8,  FUNC); \
            case Value::INT16:     CALL_FUNC(second._data.i16, FUNC); \
            case Value::INT32:     CALL_FUNC(second._data.i32, FUNC); \
            case Value::INT64:     CALL_FUNC(second._data.i64, FUNC); \
            case Value::UINT8:     CALL_FUNC(second._data.u8,  FUNC); \
            case Value::UINT16:    CALL_FUNC(second._data.u16, FUNC); \
            case Value::UINT32:    CALL_FUNC(second._data.u32, FUNC); \
            case Value::UINT64:    CALL_FUNC(second._data.u64, FUNC); \
            default: throw InvalidOperationException("Implementation error8"); \
        }                                                             \
    }


    FUNC_DEFINITION(^,std::pow);



#define ASSIGN_OP(OP)                            \
    void Value::operator OP##= (const Value& second) \
    {                                            \
        *this = *this OP second;                 \
    }


    ASSIGN_OP(+);
    ASSIGN_OP(*);
    ASSIGN_OP(/);
    ASSIGN_OP(^);
    ASSIGN_OP(%);


#define CALL_COMPARISON_OP(VALUE, OP)                                             \
   switch(_current)                                            \
        {                                                           \
            case Value::FLOAT:     return _data.f   OP VALUE; \
            case Value::DOUBLE:    return _data.d   OP VALUE; \
            case Value::LDOUBLE:   return _data.ld  OP VALUE; \
            case Value::INT8:      return _data.i8  OP VALUE; \
            case Value::INT16:     return _data.i16 OP VALUE; \
            case Value::INT32:     return _data.i32 OP VALUE; \
            case Value::INT64:     return _data.i64 OP VALUE; \
            case Value::UINT8:     return _data.u8  OP VALUE; \
            case Value::UINT16:    return _data.u16 OP VALUE; \
            case Value::UINT32:    return _data.u32 OP VALUE; \
            case Value::UINT64:    return _data.u64 OP VALUE; \
            default: throw InvalidOperationException("Implementation error9");  \
        }

#define COMPARISON_DEFINITION(OP)                                           \
    bool Value::operator OP(const Value& second) const            \
    {                                                               \
        switch(second._current)                                           \
        {                                                                 \
            case Value::FLOAT:     CALL_COMPARISON_OP(second._data.f, OP);    \
            case Value::DOUBLE:    CALL_COMPARISON_OP(second._data.d, OP);    \
            case Value::LDOUBLE:   CALL_COMPARISON_OP(second._data.ld, OP);   \
            case Value::INT8:      CALL_COMPARISON_OP(second._data.i8, OP);   \
            case Value::INT16:     CALL_COMPARISON_OP(second._data.i16, OP);  \
            case Value::INT32:     CALL_COMPARISON_OP(second._data.i32, OP);  \
            case Value::INT64:     CALL_COMPARISON_OP(second._data.i64, OP);  \
            case Value::UINT8:     CALL_COMPARISON_OP(second._data.u8, OP);   \
            case Value::UINT16:    CALL_COMPARISON_OP(second._data.u16, OP);  \
            case Value::UINT32:    CALL_COMPARISON_OP(second._data.u32, OP);  \
            case Value::UINT64:    CALL_COMPARISON_OP(second._data.u64, OP);  \
            default: throw InvalidOperationException("Implementation error10"); \
        }                                                                     \
    }

    COMPARISON_DEFINITION(==)
    COMPARISON_DEFINITION(!=)
    COMPARISON_DEFINITION(<)
    COMPARISON_DEFINITION(<=)
    COMPARISON_DEFINITION(>)
    COMPARISON_DEFINITION(>=)

    Value Value::operator%(const Value& second) const
    {                                                               
        Value result = second;                                      
                                                                    
        switch(_current)                                            
        {                                                           
            case Value::FLOAT:
            case Value::DOUBLE:
            case Value::LDOUBLE:   throw InvalidOperationException("Modulo on floating point values");
            case Value::INT8:      result %= _data.i8;  break;     
            case Value::INT16:     result %= _data.i16; break;     
            case Value::INT32:     result %= _data.i32; break;     
            case Value::INT64:     result %= _data.i64; break;     
            case Value::UINT8:     result %= _data.u8;  break;     
            case Value::UINT16:    result %= _data.u16; break;     
            case Value::UINT32:    result %= _data.u32; break;     
            case Value::UINT64:    result %= _data.u64; break;     
        }                                                           
                                                                    
        return result;                                              
    }

#define INT_DIVISION_ENABLED 0
    
    Value Value::operator/(const Value& second) const            
    {                                                               
        Value result = *this;

            switch(second._current)
            {
                case Value::FLOAT:     result /= second._data.f;   break;
                case Value::DOUBLE:    result /= second._data.d;   break;
                case Value::LDOUBLE:   result /= second._data.ld;  break;

                case Value::INT8:
                case Value::INT16:
                case Value::INT32:
                case Value::INT64:
                case Value::UINT8:
                case Value::UINT16:
                case Value::UINT32:
                case Value::UINT64:
                    if(*this > second && ((*this % second) == Value(0))) {
                        switch (second._current) {
                            case Value::INT8:   result /= second._data.i8;  break;
                            case Value::INT16:  result /= second._data.i16; break;
                            case Value::INT32:  result /= second._data.i32; break;
                            case Value::INT64:  result /= second._data.i64; break;
                            case Value::UINT8:  result /= second._data.u8;  break;
                            case Value::UINT16: result /= second._data.u16; break;
                            case Value::UINT32: result /= second._data.u32; break;
                            case Value::UINT64: result /= second._data.u64; break;
                        }
                    } else {
                        result = ((float) result) / ((float) second);
                    }
            }
        
        return result;                                              
    }

    Value Value::evaluate(const Value& val) const
    {
        return *this;
    }

    std::string Value::print()
    {
        std::ostringstream ss;

        switch(_current)
        {
            case FLOAT:     ss << _data.f; return ss.str();
            case DOUBLE:    ss << _data.d; return ss.str();
            case LDOUBLE:   ss << _data.ld; return ss.str();
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

    constexpr ArithmeticType Value::getType() const
    {
        return VAL;
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

    const Value Value::operator++(int)
    {
        Value copy(*this);
        operator++();
        return copy;
    }

    Value::operator bool() const
    {
        return *this != Value(0);
    }

    Value::Value(const std::string& input)
    {
        using namespace std::ranges;
        const auto NOT_FOUND = std::string::npos;

        if(!all_of(input, [&input](auto& e){ return isdigit(e) || e == '.' || e == ','; }))
            throw InvalidOperationException("String" + input + " does not represent a number");

        // If integer
        if(input.find(',') == NOT_FOUND && input.find('.') == NOT_FOUND) {
            if(input.front() == '-') { // If negative
                const int64_t maxRangeInt = atoi(input.c_str());

                if(maxRangeInt >= std::numeric_limits<int8_t>::min())
                    *this = Value((int8_t) maxRangeInt);
                else if(maxRangeInt >= std::numeric_limits<int16_t>::min())
                     *this = Value((int16_t) maxRangeInt);
                else if(maxRangeInt >= std::numeric_limits<int32_t>::min())
                    *this = Value((int32_t) maxRangeInt);
                else
                    *this = Value(maxRangeInt);
            }
            else {  // If positive
                const uint64_t maxRangeInt = atoi(input.c_str());

                if(maxRangeInt <= std::numeric_limits<uint8_t>::max())
                    *this = Value((uint8_t) maxRangeInt);
                else if(maxRangeInt <= std::numeric_limits<uint16_t>::max() &&
                        maxRangeInt > std::numeric_limits<int16_t>::min())
                    *this = Value((int16_t) maxRangeInt);
                else if(maxRangeInt <= std::numeric_limits<uint32_t>::max() &&
                        maxRangeInt > std::numeric_limits<int32_t>::min())
                    *this = Value((int32_t) maxRangeInt);
                else
                    *this = Value(maxRangeInt);
            }
        }   // If floating point
        else {
          const long double maxRangeFloat = atof(input.c_str());

          if(maxRangeFloat <= std::numeric_limits<float>::max() &&
                maxRangeFloat > std::numeric_limits<float>::min())
              *this = Value((float) maxRangeFloat);
          else if(maxRangeFloat <= std::numeric_limits<double>::max() &&
                  maxRangeFloat > std::numeric_limits<double>::min())
              *this = Value((double) maxRangeFloat);
          else
              *this = Value(maxRangeFloat);
        }
    }

    std::strong_ordering Value::operator<=>(const Value& o) const
    {
        if(*this == o)
            return std::strong_ordering::equal;

        if(*this > o)
            return std::strong_ordering::greater;

        return std::strong_ordering::less;
    }
}