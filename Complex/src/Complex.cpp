//
// Created by mrhowever on 28.01.20.
//

#include <algorithm>
#include "../include/Complex.hh"
#include <ArithmeticFunctions.hh>
#include <Constants.hh>

//TODO Requires TrigonometricFunctions, NaturalLogarithm
//TODO Sqrt of complex number
//

namespace MC::CN {
    template<typename T>
    Complex<T>::Complex() = default;

    template<typename T>
    Complex<T>::~Complex() = default;

    template<typename T>
    Complex<T>::Complex(T newA, T newB) : a(newA), b(newB) {}

    template<typename T>
    Complex<T>::Complex(const Complex &copy) : a(copy.a), b(copy.b) {}

    template<typename T>
    Complex<T>& Complex<T>::operator=(Complex<T> copy)
    {
        swap(*this, copy);
        return *this;
    }

    template<typename T>
    Complex<T>::Complex(Complex<T> &&move) noexcept : Complex<T>()
    {
        swap(*this, move);
    }

    template<typename T>
    void swap(Complex<T> &first, Complex<T> &second)
    {
        std::swap(first.a, second.a);
        std::swap(first.b, second.b);
    }

    template<typename T>
    T Complex<T>::real()
    {
        return a;
    }

    template<typename T>
    T Complex<T>::imag()
    {
        return b;
    }

    //TODO add ArithmeticFunctions library (possible recursive inclusion?)
//    template<typename T>
//    T Complex<T>::mod()
//    {
//        return MC::AF::mod(a,b);
//    }

//TODO Requires TrigonometricFunctions and ConstantValues
    template<typename T>
    double Complex<T>::arg()
    {
        if(a > 0 || b) {
            return 2 * MC::TF::arctan(b / (mod() + a));
        }
        else if(a < 0 && !y) {
            return MC::CV::PI;
        }
        else {
            throw new ComplexNumberException("Undefined argument value");
        }
    }

    template<typename T>
    Complex<T> Complex<T>::conjugate()
    {
        return Complex(a,-b);
    }

    template<typename T>
    Complex<T> Complex<T>::reciprocal()
    {
        return Complex(a / MC::AF::squareSum(a,b), -(b / MC::AF::squareSum(a,b)));
    }

    template<typename T>
    Complex<T> Complex<T>::operator+(const Complex& second)
    {
        return Complex(a + second.a, b + second.b);
    }

    template<typename T>
    Complex<T> Complex<T>::operator-(const Complex& second)
    {
        return Complex(a - second.a, b - second.b);
    }

    template<typename T>
    Complex<T> Complex<T>::operator*(const Complex& second)
    {
        //TODO alternate version, check performance
        //double modmult = mod() * second.mod();
        //double argsum  = arg() + second.arg();
        // return Complex(modmult*MC::TF::cos(argsum), modmult*MC::TF::sin(argsum));
        return Complex((a * second.a) - (b * second.b), (a * second.b) + (b * second.a));
    }

    template<typename T>
    Complex<T> Complex<T>::operator/(const Complex& second)
    {
        //TODO alternate version, check performance
        //double moddiv = mod() / second.mod();
        //double argsub = arg() - second.arg();
        // return Complex(moddiv*MC::TF::cos(argsub), moddiv*MC::TF::sin(argsub));

        return Complex(((second.a * a) + (second.b * b)) / (MC::AF::squareSum(a,b)),
                       ((second.b * a) - (second.a * b)) / (MC::AF::squareSum(a,b)));
    }

    template<typename T>
    Complex<T> Complex<T>::operator+=(const Complex& second)
    {
        return *this = (*this + second);
    }

    template<typename T>
    Complex<T> Complex<T>::operator-=(const Complex& second)
    {
        return *this = (*this - second);
    }

    template<typename T>
    Complex<T> Complex<T>::operator*=(const Complex& second)
    {
        return *this = (*this * second);
    }

    template<typename T>
    Complex<T> Complex<T>::operator/=(const Complex& second)
    {
        return *this = (*this / second);
    }

    template<typename T>
    bool Complex<T>::operator==(const Complex& second)
    {
        return a == second.a && b == second.b;
    }

    template<typename T>
    bool Complex<T>::operator!=(const Complex& second)
    {
        return !(*this == second);
    }
}