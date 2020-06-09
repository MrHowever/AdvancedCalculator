//
// Created by mrhowever on 14.11.19.
//

#ifndef BIGINTEGER_ARITHMETICFUNCTIONS_HH
#define BIGINTEGER_ARITHMETICFUNCTIONS_HH

#include <type_traits>
#include <BitShiftable.hh>
#include <cmath>
#include "ArithmeticFunctionException.hh"

//TODO Lucas sequence (Requires matrices)
//TODO Negative squares and roots (Requires complex numbers)
//TODO S = a + b*i squares (Requires complex numbers)

namespace MC::AF
{
                             // Library interface

    const double CALC_ACC = 0.000000000000001;

    template<typename T, typename P> T pow(T, P);
    template<typename T> T montgomeryLadder(T,T);
    template<typename T, typename P> double root(T,P,double = CALC_ACC);
    template<typename T> double sqrt(T, double = CALC_ACC);
    template<typename T> double mod(T,T);
    template<typename T> T squareSum(T,T);

    enum EstimationType : int {LINEAR, HYPERBOLIC, ARITHMETIC, BINARY, FLOAT, FLOAT_RECIPROCAL};

    template<typename T> double __initialEstimate(T value, EstimationType = LINEAR);
    template<typename T> double __babylonianSqrt(T,double = CALC_ACC);
    template<typename T> double __twoVarSqrt(T,double = CALC_ACC);
    template<typename T> double __newtonSqrt(T,double = CALC_ACC);
    template<typename T> double __halleySqrt(T,double = CALC_ACC);
    template<typename T> double __goldschmidtSqrt(T,double = CALC_ACC);
    template<typename T> double __goldschmidtSqrtReciprocal(T,double = CALC_ACC);
    template<typename T> double __fusedGoldschmidtSqrt(T,double = CALC_ACC);
    template<typename T> double __fusedGoldschmidtSqrtReciprocal(T,double = CALC_ACC);
    template<typename T> double __fractionExpansionSqrt(T,double = CALC_ACC);

    template<typename T, typename P> double __exponentialRoot(T,P,double = CALC_ACC);


                            // Library implementation

    // Exponentiation by squaring
    template<typename T, typename P>
    T pow(T base, P power) {
        if constexpr(std::is_base_of_v<MC::BitShiftable<P>, P> || std::is_integral_v<P>) {
            T result = 1;

            while (power) {
                if (power & 1)
                    result *= base;

                base *= base;
                power >>= 1;
            }

            return result;
        }
        else
            throw ArithmeticFunctionException("Power must be an integer");
    }

    // Exponentiation using Montgomery's ladder technique which is slower but provides defence against
    // side-channel attacks
    template<typename T>
    T montgomeryLadder(T base, T power)
    {
        if(!power)
            return 1;

        T baseOne = base;
        T squaredBase = base*base;
        T k = 0;//binaryLength(power);

        for(T i = k - 2; i >= 0; i--) {
            if(((power >> i) & 1) == 0) {
                squaredBase *= baseOne;
                baseOne *= baseOne;
            }
            else {
                baseOne *= squaredBase;
                squaredBase *= squaredBase;
            }
        }

        return baseOne;
    }

    // Fast converging nth order root algorithm
    template<typename T, typename P>
    double root(T base, P order, const double precision)
    {
        // Handle zero base case and zero power case
        if(!base)
            return base;

        if(!order)
            throw ArithmeticFunctionException("Order of a root cannot be 0.");

        double initial = base / order;              // Initial estimate
        double delta;
        const double inverseOrder = 1.0 / order;
        const P subtractedOrder = order - 1;

        //TODO change to custom abs
        do
        {
            delta = inverseOrder * (base / pow(initial,subtractedOrder) - initial);
            initial += delta;
        } while (std::abs(delta) > precision);

        return initial;
    }

    //TODO mvoe as an external number type class
    template<typename T>
    std::pair<double,uint64_t> exponentDecimalForm(T value)
    {
        uint64_t power = 0;

        while(value > 100.0) {
            value /= 100.0;
            power += 2;
        }

        return std::make_pair(value,power);
    }

    template<typename T>
    std::pair<double,uint64_t> exponentBinaryForm(T value)
    {
        if constexpr (std::is_floating_point_v<T>) {
            int exponent = 0;
            double val = frexp(value,&exponent);
            return std::make_pair(val,exponent);
        }
        else
            throw ArithmeticFunctionException("Parameter type must be a floating point type.");
    }

    // Square root value estimation lookup table for arithmetic estimation method
    const uint lookupTable[] = {1,1,1,
                                2,2,2,2,
                                3,3,3,3,3,3,
                                4,4,4,4,4,4,4,4,
                                5,5,5,5,5,5,5,5,5,5,
                                6,6,6,6,6,6,6,6,6,6,6,6,
                                7,7,7,7,7,7,7,7,7,7,7,7,7,7,
                                8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
                                9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,
                                10,10,10,10,10,10,10,10,10,10};

    template<typename T>
    double __initialEstimate(T value, EstimationType type)
    {
        switch(type)
        {
            // Decimal linear estimate (most accurate on average)
            case LINEAR: {
                auto exponential = exponentDecimalForm(value);
                return (exponential.first < 10.0) ? (0.28  * exponential.first + 0.89) * pow(10, exponential.second / 2) :
                                                    (0.089 * exponential.first + 2.8)  * pow(10, exponential.second / 2);
            }

            // Remaining methods are either very fast or very accurate but only for select
            // group of values and are worse than linear estimation on average for arbitrary input

            // Decimal hyperbolic estimate
            case HYPERBOLIC: {
                auto exponential = exponentDecimalForm(value);
                double base = exponential.first;
                uint64_t exponent = exponential.second != 1 ? exponential.second / 2 : 1;
                return ((-190.0/(base + 20.0)) + 10.0) * pow(10.0,exponent);
            }

            // Decimal arithmetic estimate
            case ARITHMETIC: {
                auto exponential = exponentDecimalForm(value);
                double base = exponential.first;
                uint64_t exponent = exponential.second != 1 ? exponential.second / 2 : 1;
                //TODO use custom round
                return lookupTable[(uint) std::round(base)] * pow(10,exponent);
            }

            // Binary estimate
            case BINARY: {
                auto exponential = exponentBinaryForm(value);
                double base = exponential.first;
                uint64_t exponent = exponential.second;
                return (0.485 + 0.485*base) * pow(2.0,exponent/2);
            }

            // Floating point value bit manipulation (The fastest method)
            case FLOAT: {
                float val = value;
                uint32_t integer_val = *(int*) &val;
                integer_val = (1u << 29u) + (integer_val >> 1u) - (1u << 22u) - 0x4B0D2;
                return *(float*) &integer_val;
            }

            case FLOAT_RECIPROCAL: {
                float half = 0.5f * (float) value;

                union {
                    float x;
                    uint32_t i;
                } u;

                u.x = (float) value;
                u.i = 0x5F375A86 - (u.i >> 1u);

                //TODO how many iterations? each increases accuracy
                for(int i = 0; i < 10; i++)
                    u.x *= (1.5f - half*pow(u.x,2));

                return u.x;
            }
        }
    }

    template<typename T>
    double sqrt(T value)
    {
        double initial = __initialEstimate(value);

        return 0;
    }

    template<typename T>
    double __babylonianSqrt(T value, double accuracy)
    {
        double approximation = __initialEstimate(value);
        double delta;

        do {
            delta = -0.5*(approximation - value / approximation);
            approximation += delta;
        } while (delta > accuracy);

        return approximation;
    }

//    template<typename T, typename P>
//    double __exponentialRoot(T value, P order)
//    {
//        return exp((1 / order) * ln(value));
//    }
//

//TODO can be generalized to any root order
    template<typename T>
    double __twoVarSqrt(T value, double accuracy)
    {
        if(value <= 0 || value >= 3)
            throw ArithmeticFunctionException("Value for this sqrt method needs to be in range (0;3).");

        double initial = value;
        double secondVar = initial - 1.0;

        do {
            initial -= (initial*secondVar)/2.0;
            secondVar = (pow(secondVar,2)*(secondVar - 3.0)) / 4.0;
            //TODO swap to custom abs
        } while(std::abs(secondVar) > accuracy);

        return initial;
    }

//
//      TODO for all the functions below swap division of estimate by value to get reciprocal to LUT
//

    template<typename T>
    double __newtonSqrt(T value, double accuracy)
    {
        double initial = __initialEstimate(value) / value;
        double delta;

        do {
            delta = 0.5*initial*(1.0 - (value * pow(initial,2)));
            initial += delta;
            //TODO swap for custom abs
        } while(std::abs(delta) > accuracy);

        return initial * value;
    }

    template<typename T>
    double __halleySqrt(T value, double accuracy)
    {
        double initial = __initialEstimate(value) / value;
        double delta, y;

        do {
            y = value * pow(initial,2);
            delta = (initial / 8.0) * (7.0 - (y * (10 - 3*y)));
            initial += delta;
            //TODO swap for custom abs
        } while(std::abs(delta) > accuracy);

        return initial * value;
    }

    template<typename T>
    double __goldschmidtSqrt(T value, double accuracy)
    {
        double b = value;
        double Y = __initialEstimate(value) / value;
        double x = value*Y;

        do {
           b *= pow(Y,2);
           Y = (3.0 - b) / 2.0;
           x *= Y;
        } while ( abs(b - 1) > accuracy);

        return x;
    }

    template<typename T>
    double __goldschmidtSqrtReciprocal(T value, double accuracy)
    {
        double b = value;
        double Y = __initialEstimate(value) / value;
        double y = Y;

        do {
            b *= pow(Y,2);
            Y = (3.0 - b) / 2.0;
            y *= Y;
        } while ( abs(b - 1) > accuracy);

        return y;
    }

    //TODO ensure that FAM commands are used
    template<typename T>
    double __fusedGoldschmidtSqrt(T value, double accuracy)
    {
        double y = __initialEstimate(value) / value;
        double x = value * y;
        double h = y / 2.0;
        double r;

        do {
            r = 0.5 - x*h;
            x += x*r;
            h += h*r;
        } while ( abs(r) > accuracy);

        return x;
    }

    template<typename T>
    double __fusedGoldschmidtSqrtReciprocal(T value, double accuracy)
    {
        double y = __initialEstimate(value) / value;
        double x = value * y;
        double h = y / 2.0;
        double r;

        do {
            r = 0.5 - x*h;
            x += x*r;
            h += h*r;
        } while ( abs(r) > accuracy);

        return 2*h;
    }

    template<typename T>
    double __fractionExpansionSqrt(T value, double accuracy)
    {
        double initial = __initialEstimate(value);
        double remainder = value - pow(initial,2);
        uint64_t depth = 10;    //TODO how to determine depth?

        double fraction = remainder / (2 * initial);

        for(int i = 0; i < depth; i++) {
            fraction = remainder / (2 * initial + fraction);
        }

        return initial + fraction;
    }

    template<typename T>
    double mod(T first, T second)
    {
        return sqrt(squareSum(first,second));
    }

    template<typename T>
    T squareSum(T first, T second)
    {
        return pow(first,2) + pow(second,2);
    }
}

#endif //BIGINTEGER_ARITHMETICFUNCTIONS_HH
