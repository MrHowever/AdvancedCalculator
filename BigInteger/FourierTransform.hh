//
// Created by mrhowever on 05.11.19.
//

#ifndef BIGINTEGER_FOURIERTRANSFORM_HH
#define BIGINTEGER_FOURIERTRANSFORM_HH

#include <vector>
#include <stdint.h>
#include <algorithm>
#include <math.h>
#include <limits.h>
#include <iostream>
#include "BasicOperations/BasicOperations.hh"
#include "../Prime/Prime.hh"
#include "../Totients/Totients.hh"
#include "../IntegerFactorization/PrimeFactorization.hh"
#include "../ArithmeticFunctions/ArithmeticFunctions.hh"

namespace MC
{
    namespace FT
    {
        template<typename T>
        std::vector<T> fft(const std::vector<T>& input)
        {

        }


        //Cooley-Tukey
        template<typename T>
        std::vector<T> __ntt(const std::vector<T>& input, T omega, T modulus, bool inverse = false)
        {
            if(input.size() == 1)
                return input;

            std::vector<T> even;
            std::vector<T> odd;

            for(int i = 0; i < input.size(); i++) {
                if(i % 2 == 0)
                    even.push_back(input[i]);
                else
                    odd.push_back(input[i]);
            }


            even = __ntt(even, MO::modularPow<T>(omega, 2, modulus), modulus);
            odd = __ntt(odd, MO::modularPow<T>(omega, 2, modulus), modulus);

            std::vector<T> result(input.size());

            uint64_t halfSize = input.size() / 2;

            for(int i = 0; i < halfSize; i++) {
                T prod = MO::modularMult<T>(MO::modularPow<T>(omega,i,modulus),odd[i],modulus);
                result[i] = MO::modularAdd(even[i],prod,modulus);
                result[i + halfSize] = MO::modularSub(even[i],prod,modulus);
            }

            return result;
        }



        template<typename T>
        struct NTTParams
        {
           T omega;
           T modulus;
        };

        // Number theoretic transform using Cooley-Tukey method
        template<typename T>
        std::pair<std::vector<T>, NTTParams<T>> ntt(std::vector<T>& input)
        {
            T maxElement = BO::max(input);

            // If size isn't a power of 2
            if((input.size() & input.size() - 1) != 0) {
                auto paddingSize = (size_t) std::round(std::pow(2,std::ceil(std::log2(input.size())))) - input.size();
                input.insert(input.end(),paddingSize,0);
            }

            if(BO::max<T>() - maxElement <= input.size()) {
                //TODO throw exception for overflow
            }

            T modulus = 337; //BO::max(maxElement,input.size()) + 1;
            //T totient = modulus - 1;
            //T generator = findGenerator(totient,modulus);
            T omega = 85; //MO::modularPow(generator, totient / input.size(),modulus);

            return std::pair<std::vector<T>,NTTParams<T> >(__ntt(input,omega,modulus), {omega,modulus});
        }

        template<typename T>
        std::vector<T> intt(const std::vector<T>& transform, NTTParams<T> params)
        {
            std::vector<T> result(transform);
            result = __ntt(result,MO::reciprocal<T>(params.omega,params.modulus),params.modulus,true);

            //TODO check if for loop wont be faster
            std::transform(result.begin(),result.end(),result.begin(),
                            [&params,&transform](auto e){ return MO::modularMult(e,MO::reciprocal<T>(transform.size(),params.modulus),params.modulus);});

            return result;
        }

        constexpr uint64_t powerOf2(uint i)
        {
            uint64_t temp = 1;

            for(uint64_t j = 0; j < i; j++) {
                temp *= 2;
            }

            return temp;
        }

        template<uint64_t AS>
        constexpr std::array<uint64_t,AS> fillPowerArray()
        {
            std::array<uint64_t,AS> luTable{0};

            for(uint64_t i = 0; i < AS; i++) {
                luTable[i] = powerOf2(i);
            }

            return luTable;
        }

        static constexpr std::array<uint64_t,64> powersOf2 = fillPowerArray<64>();

        //Cooley-Tukey
        template<typename T>
        std::vector<T> __fnt(const std::vector<T>& input, T omega, T modulus, T omegaPower, bool inverse = false)
        {
            if(input.size() == 1)
                return input;

            uint64_t halfSize = input.size() >> 1;

            std::vector<T> even;
            std::vector<T> odd;

            even.reserve(halfSize);
            odd.reserve(halfSize);

            for(uint i = 0; i < input.size(); i++) {
                i & 1u ? odd.push_back(input[i]) : even.push_back(input[i]);
            }

/*
            even = __fnt(even, powersOf2[omegaPower << 1] % modulus, modulus, omegaPower << 1);
            odd = __fnt(odd, powersOf2[omegaPower << 1] % modulus,modulus, omegaPower << 1);
*/
            T c = powersOf2[omegaPower << 1u];
            T a = c % modulus;
            T b = MO::modularPow<T>(omega, 2, modulus);

            even = __fnt(even, MO::modularPow<T>(omega, 2, modulus), modulus, omegaPower << 1u);
            odd = __fnt(odd, MO::modularPow<T>(omega, 2, modulus),modulus, omegaPower << 1u);

            std::vector<T> result(input.size());

            for(int i = 0; i < halfSize; i++) {
                T prod = MO::modularMult<T>(MO::modularPow<T>(omega,i,modulus),odd[i],modulus);
                result[i] = MO::modularAdd(even[i],prod,modulus);
                result[i + halfSize] = MO::modularSub(even[i],prod,modulus);
            }

            return result;
        }

        template<typename T>
        std::pair<std::vector<T>, NTTParams<T>> fnt(std::vector<T>& input, T modulus, T omega = 2)
        {

            static_assert(powersOf2[1] == 2);

            // If size isn't a power of 2
            if((input.size() & (input.size() - 1)) != 0) {
                auto paddingSize = (size_t) std::round(std::pow(2,std::ceil(std::log2(input.size())))) - input.size();
                input.insert(input.end(),paddingSize,0);
            }

            // Check if modulus is of form 2^k + 1
            if(((modulus - 1) & (modulus - 2)) != 0) {
                //TODO throw fourier exception
            }

            // Check if omega is a power of 2
            if((omega & (omega - 1)) != 0) {
                //TODO throw fourier exception
            }

            T omegaPower = 1;

            return std::pair<std::vector<T>,NTTParams<T> >(__fnt(input,omega,modulus,omegaPower), {omega,modulus});
        }

        template<typename T>
        std::vector<T> ifnt(const std::vector<T>& transform, T modulus, T omega = 2)
        {
            // Check if modulus is of form 2^k + 1
            if(((modulus - 1) & (modulus - 2)) != 0) {
                //TODO throw fourier exception
            }

            // Check if omega is a power of 2
            if((omega & (omega - 1)) != 0) {
                //TODO throw fourier exception
            }

            T omegaPower = 1;
            std::vector<T> result(transform);
            result = __fnt(result,MO::reciprocal<T>(omega,modulus),modulus, omegaPower,true);

            //TODO check if for loop wont be faster
            std::transform(result.begin(),result.end(),result.begin(),
                           [modulus,omega,&transform](auto e){ return MO::modularMult(e,MO::reciprocal<T>(transform.size(),modulus),modulus);});

            return result;
        }
    }
}

#endif //BIGINTEGER_FOURIERTRANSFORM_HH
