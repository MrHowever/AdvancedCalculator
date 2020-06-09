#ifndef BIGINTEGER_BIGINTEGER_HH
#define BIGINTEGER_BIGINTEGER_HH

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <limits.h>
#include "../Random/Randomizable.hh"
#include "../Interfaces/Comparable.hh"
#include "../Interfaces/BitShiftable.hh"

//TODO make sure implicit conversion in SignedInteger/UnsignedInteger methods are impossible
//TODO make sure that no operation leaves multiple cells with 0 value in the front

class BigInteger : public MC::Randomizable<BigInteger>, MC::Comparable<BigInteger>, MC::BitShiftable<BigInteger>
{

    bool _negative;
    const uint64_t DIGIT_MAX = std::numeric_limits<uint64_t>::max();
    const uint8_t BITS_PER_DIGIT = 64;

    //TODO implement

    template<typename E, typename G>
    static BigInteger random(const E&, const G&);
    template<typename E, typename G>
    static BigInteger random(BigInteger, BigInteger, const E&, const G&);
    template<typename E, typename G>
    static BigInteger random(BigInteger, bool, const E&, const G&);
    template<typename E, typename G, typename D>
    static BigInteger random(const E&, const G&, const D&);
    template<typename E, typename G, typename D>
    static BigInteger random(BigInteger, BigInteger, const E&, const G&,const D&);
    template<typename E, typename G, typename D>
    static BigInteger random(BigInteger, bool, const E&, const G&, const D&);

public:
    std::vector<uint64_t> _digits;
    //Constructors
    BigInteger();
    // IMPORTANT pointer has to be used here, otherwise it breaks (probably because the 0 assignment
   template<typename T> explicit BigInteger(T); // For primitive types
   // explicit BigInteger(double);                    // TODO For floating point types//  //
   BigInteger(std::string, uint base);             // For strings
    BigInteger(const BigInteger&);                  // Copy constructor
    BigInteger(BigInteger&&) noexcept;              // Move constructor
//TODO make private
    explicit BigInteger(std::vector<uint64_t>);
public:
    ~BigInteger();                                  // Destructor

    // Assignment operators
    BigInteger& operator=(const BigInteger&);
    template<typename T> BigInteger& operator=(T);
    //BigInteger& operator=(const double&);   //TODO
    BigInteger& operator=(BigInteger&&) noexcept;

    // Conversion operators
    explicit operator int8_t() const;
    explicit operator int16_t() const;
    explicit operator int32_t() const;
    explicit operator int64_t() const;
    explicit operator uint8_t() const;
    explicit operator uint16_t() const;
    explicit operator uint32_t() const;
    explicit operator uint64_t() const;
    //TODO explicit operator double() const;
    //TODO explicit operator long double() const;
    //TODO explicit operator float() const;
    explicit operator std::string() const;

    // Arithmetic operators

//TODO optimize -= and += operators for primmitve types to not use unneccessary copies by assigning result of -/+ operation
    BigInteger operator+(const BigInteger&) const;
    BigInteger& operator+=(const BigInteger&);
    BigInteger operator+() const;
    BigInteger operator-(const BigInteger&) const;
    BigInteger& operator-=(const BigInteger&);
    BigInteger operator-() const;
    BigInteger operator*(const BigInteger&) const;
    BigInteger& operator*=(const BigInteger&);
    BigInteger operator/(const BigInteger&) const;
    BigInteger& operator/=(const BigInteger&);
    BigInteger operator%(const BigInteger&) const;
    BigInteger& operator%=(const BigInteger&);
    BigInteger& operator++();                       // This should return reference
    const BigInteger operator++(int);                     // This should not
    BigInteger& operator--();
    const BigInteger operator--(int);

    template<typename T> BigInteger  operator+(const T) const;
    template<typename T> BigInteger& operator+=(const T);
    template<typename T> BigInteger  operator-(const T) const;
    template<typename T> BigInteger& operator-=(const T);
    template<typename T> BigInteger operator*(const T) const;
    template<typename T> BigInteger operator*=(const T);
    template<typename T> BigInteger operator/(const T) const;
    template<typename T> BigInteger operator/=(const T);
    template<typename T> BigInteger  operator%(const T) const;
    template<typename T> BigInteger& operator%=(const T);

    // Bitwise operators
    BigInteger operator&(const BigInteger&) const;
    BigInteger& operator&=(const BigInteger&);
    BigInteger operator|(const BigInteger&) const;
    BigInteger& operator|=(const BigInteger&);
    BigInteger operator<<(const BigInteger&) const override;
    BigInteger& operator<<=(const BigInteger&) override;
    BigInteger operator>>(const BigInteger&) const override;
    BigInteger& operator>>=(const BigInteger&) override;
    BigInteger operator~() const;
    BigInteger operator^(const BigInteger&) const;
    BigInteger& operator^=(const BigInteger&);

    // In-place shift operators
    BigInteger operator<<(uint64_t) const override;
    BigInteger& operator<<=(uint64_t) override;
    BigInteger operator>>(uint64_t) const override;
    BigInteger& operator>>=(uint64_t) override;

    // Resizing shift methods
    BigInteger shiftLeft(uint64_t) const;
    BigInteger shiftLeft(const BigInteger&) const;

    BigInteger operator&(uint64_t) const;
    BigInteger& operator&=(uint64_t);
    BigInteger operator|(uint64_t) const;
    BigInteger& operator|=(uint64_t);
    BigInteger operator^(uint64_t) const;
    BigInteger& operator^=(uint64_t);

    // Comparison operators
    bool operator==(const BigInteger&) const override;
    bool operator!=(const BigInteger&) const override;
    bool operator>(const BigInteger&) const override;
    bool operator<(const BigInteger&) const override;
    bool operator>=(const BigInteger&) const override;
    bool operator<=(const BigInteger&) const override;

    // Comparison operators for primitive types
    template<typename T> bool operator==(T) const;
    template<typename T> bool operator!=(T) const;
    template<typename T> bool operator>(T) const;
    template<typename T> bool operator<(T) const;
    template<typename T> bool operator>=(T) const;
    template<typename T> bool operator<=(T) const;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    std::string toString(int = 10) const;

    class Base
    {
        int B;

        std::vector<int> _baseDigits;

        std::vector<int> separateDigits(uint64_t);
        std::vector<int> add(std::vector<int>,std::vector<int>);
        std::vector<int> multiplicate(std::vector<int>,std::vector<int>);

    public:
        explicit Base(const BigInteger&,int);
        std::string toString();
    };


    BigInteger karatsubaMultiplication(const BigInteger&);
    BigInteger toomCookMultiplication(const BigInteger&);

    template<typename T> friend BigInteger pow(const BigInteger&, const T);
public:
    BigInteger fftMultiplication(const BigInteger&);    //TODO

private:

    // Utilities
    static uint8_t charToNumber(char);
    BigInteger newtonRaphsonDiv(const BigInteger&); //TODO
    BigInteger schoolbookMultiplication(const BigInteger&) const;
    std::vector<BigInteger> splitIntoParts(uint64_t) const;
};

// Math operations
BigInteger abs(const BigInteger&);
//BigInteger pow(const BigInteger&, const BigInteger&);   //toimplement TODO

std::istream& operator>>(std::istream&, const BigInteger&);

template<typename T> bool operator==(T, const BigInteger&);
template<typename T> bool operator>(T, const BigInteger&);
template<typename T> bool operator<(T, const BigInteger&);
template<typename T> bool operator>=(T, const BigInteger&);
template<typename T> bool operator<=(T, const BigInteger&);
template<typename T> bool operator!=(T, const BigInteger&);

uint64_t operator&(const uint64_t&, const BigInteger&);
uint64_t& operator&=(uint64_t&, const BigInteger&);
uint64_t operator|(const uint64_t&, const BigInteger&);
uint64_t& operator|=(uint64_t&, const BigInteger&);
uint64_t operator<<(const uint64_t&, const BigInteger&);
uint64_t& operator<<=(uint64_t&, const BigInteger&);
uint64_t operator>>(const uint64_t&, const BigInteger&);
uint64_t& operator>>=(uint64_t&, const BigInteger&);
uint64_t operator^(const uint64_t&, const BigInteger&);
uint64_t& operator^=(uint64_t&, const BigInteger&);

static const BigInteger BASE("18446744073709551616",10);
static const BigInteger ZERO(0);


namespace MC {
    typedef uint64_t Digit;

    //TODO generalize for every vector input?
    std::vector<Digit> fft(const std::vector<Digit>&);

}

#endif //BIGINTEGER_BIGINTEGER_HH