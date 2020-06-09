//
// Created by mrhowever on 28.01.20.
//

#ifndef COMPLEX_COMPLEX_HH
#define COMPLEX_COMPLEX_HH

namespace MC::CN
{
    template<typename T>
    class Complex {
        T a;
        T b;

    public:
        Complex();
        Complex(T, T);
        Complex(const Complex&);
        Complex(Complex &&) noexcept;
        ~Complex();
        Complex& operator=(Complex);
        friend void swap(Complex&,Complex&);

        T real();
        T imag();
        double mod();
        double arg();
        Complex conjugate();
        Complex reciprocal();

        Complex operator+(const Complex&);
        Complex operator-(const Complex&);
        Complex operator*(const Complex&);
        Complex operator/(const Complex&);
        Complex operator+=(const Complex&);
        Complex operator-=(const Complex&);
        Complex operator*=(const Complex&);
        Complex operator/=(const Complex&);

        bool operator==(const Complex&);
        bool operator!=(const Complex&);
    };
}

#endif //COMPLEX_COMPLEX_HH
