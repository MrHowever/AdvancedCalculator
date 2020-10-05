#ifndef FUNCTIONS_VALUE_HH
#define FUNCTIONS_VALUE_HH

#include "ArithmeticObject.hh"
#include "Typedefs.hh"

#include <cstdint>

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
        Value(const std::string&);
        Value(const Value&)            = default;
        Value(Value&&)                 = default;
        ~Value() override              = default;
        Value& operator=(Value const&) = default;

        template<Primitive T> explicit Value(T);
        template<Primitive T> Value& operator=(T);

        template<Primitive T> void operator+=(const T&);
        template<Primitive T> void operator*=(const T&);
        template<Primitive T> void operator/=(const T&);
        template<Primitive T> void operator^=(const T&);
        template<Primitive T> void operator%=(const T&);
        void operator+=(const Value&);
        void operator*=(const Value&);
        void operator/=(const Value&);
        void operator^=(const Value&);
        void operator%=(const Value&);

        [[nodiscard]] Value operator+(const Value&) const;
        [[nodiscard]] Value operator*(const Value&) const;
        [[nodiscard]] Value operator/(const Value&) const;
        [[nodiscard]] Value operator^(const Value&) const;
        [[nodiscard]] Value operator%(const Value&) const;

        Value& operator++();
        const Value operator++(int);

        [[nodiscard]] bool operator==(const Value&) const;
        [[nodiscard]] bool operator!=(const Value&) const;
        [[nodiscard]] bool operator<(const Value&) const;
        [[nodiscard]] bool operator<=(const Value&) const;
        [[nodiscard]] bool operator>(const Value&) const;
        [[nodiscard]] bool operator>=(const Value&) const;
        [[nodiscard]] std::strong_ordering operator<=>(const Value&) const;

        template<Primitive T> [[nodiscard]] bool operator<(const T&) const;
        template<Primitive T> [[nodiscard]] bool operator<=(const T&) const;
        template<Primitive T> [[nodiscard]] bool operator>(const T&) const;
        template<Primitive T> [[nodiscard]] bool operator>=(const T&) const;

        [[nodiscard]] Value evaluate(const Value&) const override;
        [[nodiscard]] constexpr ArithmeticType getType() const override;
        [[nodiscard]] std::string print() override;

        template<Primitive T> [[nodiscard]] operator T() const;

        explicit operator bool() const;
    };

    template<Primitive T> [[nodiscard]] Value operator+(const T&, const Value&);
    template<Primitive T> [[nodiscard]] Value operator*(const T&, const Value&);
    template<Primitive T> [[nodiscard]] Value operator/(const T&, const Value&);
    template<Primitive T> [[nodiscard]] Value operator^(const T&, const Value&);

    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator+(const T&, const P&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator*(const T&, const P&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator/(const T&, const P&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator^(const T&, const P&);

    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator+(const P&, const T&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator*(const P&, const T&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator/(const P&, const T&);
    template<Arithmetic T, Primitive P> [[nodiscard]] ArithmeticPointerWrapper operator^(const P&, const T&);
}

#endif //FUNCTIONS_VALUE_HH

#include "Value.tcc"
