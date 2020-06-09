//
// Created by mrhowever on 11.02.2020.
//

#ifndef FUNCTIONS_VALUE_HH
#define FUNCTIONS_VALUE_HH

#include <cstdint>
#include <string>
#include <list>
#include "ArithmeticObject.hh"

namespace MC::FN
{
    class Value : public ArithmeticObject {
        union Data {
            float        f;
            double       d;
            long double ld;
            int8_t      i8;
            int16_t    i16;
            int32_t    i32;
            int64_t    i64;
            uint8_t     u8;
            uint16_t   u16;
            uint32_t   u32;
            uint64_t   u64;
            //BigInteger bi;
            //BigDouble bd;
        };

        enum CurrentType : int {
            FLOAT = 0, DOUBLE = 1,
            LDOUBLE = 2, INT8 = 3,
            INT16 = 4, INT32 = 5,
            INT64 = 6, UINT8 = 7,
            UINT16 = 8, UINT32 = 9,
            UINT64 = 10 //, BIGINT = 11,
            //BIGDOUBLE = 12
        };

        Data _data;
        CurrentType _current;

    public:
        Value();
        Value(const Value&)            = default;
        Value(Value&&)                 = default;
        ~Value()                       = default;
        Value& operator=(const Value&) = default;

        template<typename T> explicit Value(T);
        template<typename T> Value& operator=(T);

        template<typename T> void operator+=(const T&);
        template<typename T> void operator*=(const T&);
        template<typename T> void operator/=(const T&);
        void operator+=(const Value&);
        void operator*=(const Value&);
        void operator/=(const Value&);

        [[nodiscard]] Value operator+(const Value&) const;
        [[nodiscard]] Value operator*(const Value&) const;
        [[nodiscard]] Value operator/(const Value&) const;

        Value& operator++();
        Value operator++(int);

        [[nodiscard]] bool operator==(const Value&) const;
        [[nodiscard]] bool operator!=(const Value&) const;
        [[nodiscard]] bool operator<(const Value&) const;
        [[nodiscard]] bool operator<=(const Value&) const;
        [[nodiscard]] bool operator>(const Value&) const;
        [[nodiscard]] bool operator>=(const Value&) const;

        template<typename T> [[nodiscard]] bool operator<(const T&) const;
        template<typename T> [[nodiscard]] bool operator<=(const T&) const;
        template<typename T> [[nodiscard]] bool operator>(const T&) const;
        template<typename T> [[nodiscard]] bool operator>=(const T&) const;

        void simplify() override;
        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] ArithmeticType getType() const override;
        [[nodiscard]] std::string print() const override;

        operator bool() const;
    };
}

#endif //FUNCTIONS_VALUE_HH