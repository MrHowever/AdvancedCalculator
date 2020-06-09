//
// Created by mrhowever on 12.11.19.
//

#ifndef BIGINTEGER_MODULAROPERATIONS_HH
#define BIGINTEGER_MODULAROPERATIONS_HH

#include "../BigInteger/Interfaces/BitShiftable.hh"
#include "../BigInteger/ArithmeticFunctions/ArithmeticFunctions.hh"

namespace MC
{
    namespace MO
    {
        //TODO WAY worse than standard modulo. Maybe useful for BigInteger modulo?
        template<typename T>
        T fermatMod(T base, T powerOfTwo, T modulus)
        {
            constexpr auto baseSize = sizeof(T) * 8;
            auto partSize = BO::max<uint64_t>() >> (64 - powerOfTwo);
            T result = base & partSize;

            uint i = 1;
            while(base >>= powerOfTwo)
            {
                if(i++ & 1)
                    result -= base & partSize;
                else
                    result += base & partSize;
            }

            while(result < 0)
                result += modulus;

            while(result > modulus)
                result -= modulus;


            return result;
        }
        
        template<typename T>
        T modularAdd(T a, T b, T modulus)
        {
            a %= modulus;
            b %= modulus;

            if(a < BO::max<T>() - b)
                return (a + b) % modulus;
            else
                return BO::max(a,b) - (modulus - BO::min(a,b));
        }

        template<typename T>
        T modularSub(T a, T b, T modulus)
        {
            a %= modulus;
            b %= modulus;

            return a < b ? modulus - (b - a) : a - b;
        }

        //Function calculating modular multiplicative of two numbers
        //using Russian peasant mutliplication
        template<typename T>
        T modularMult(T a,T b,T modulus)
        {
            T sum = 0;

            a %= modulus;
            b %= modulus;

            //If a*b is smaller than modulus, it cant be multiplied normally
            //However we can't check this condition by checking a*b because if
            //a*b is not smaller than modulus it might overflow and then the false
            //result might be smaller than modulus which is false. That's why we have
            //to change the order of operations and first divide modulus by a
            if (a == 0 || b < modulus / a)
                return (a * b) % modulus;

            while(b>0)
            {
                //If b is odd add a to sum
                if(b & 1)
                    sum = modularAdd(sum,a,modulus);

                //Multiply a by 2 under modulus
                if(a <= BO::max<T>() / 2)
                    a = (2*a) % modulus;
                else
                    a -= modulus - a;

                //Divide b by 2
                b >>= 1;
            }

            return sum;
        }

        //Exponentation through squaring
        template<typename T>
        T modularPow(T base, T power, T modulus) {
            if(power == 1)
                return base;

            base %= modulus;

            T result = 1;

            while (power > 0) {
                if (power & 1)
                    result = MO::modularMult(result, base, modulus);

                base = MO::modularMult(base, base, modulus);

                if constexpr(std::is_base_of_v<BitShiftable<T>, T> || std::is_integral_v<T>)
                    power >>= 1;
                else
                    power /= 2;
            }

            return result;
        }

        //Function calculating modular multiplicative inverse using extended
        //Euclidean algorithm
        template<typename T>
        T multiplicativeInvPow(T base, T modulus) {
            T modulus0 = modulus;
            T y = 0, x = 1;
            T q, t;

            if (modulus == 1)
                return 0;

            while (base > 1) {
                q = base / modulus;
                t = modulus;

                modulus = base % modulus;
                base = t;
                t = y;

                y = MO::modularSub(x, MO::modularMult(q ,y,modulus0), modulus0);
                x = t;
            }

            if (x < 0)
                x += modulus0;

            return x;
        }

        template<typename T>
        const auto reciprocal = multiplicativeInvPow<T>;
    }
}

#endif //BIGINTEGER_MODULAROPERATIONS_HH
