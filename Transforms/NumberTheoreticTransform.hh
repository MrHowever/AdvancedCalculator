//
// Created by mrhowever on 18.11.19.
//

#ifndef BIGINTEGER_NUMBERTHEORETICTRANSFORM_HH
#define BIGINTEGER_NUMBERTHEORETICTRANSFORM_HH

#include <list>

namespace MC {
    namespace MT {

        const bool NTT_AUTO_PADDING = true;
        const bool NTT_SAFETY_CHECKS = true;

        template<typename T>
        class NumberTheoreticTransform {
        protected:
            // Transform parameters
            T _omega;
            T _modulus;
            T _k;
            size_t _transformLength;
            size_t _maxN;
            bool _fft;

            // Parameters calculation
            static inline T generateOmega(size_t,T);
            static inline size_t calculateNMax(T);

            //TODO those methods dont need to be really virtual
        private:
            virtual inline T generateModulus(size_t,T);
            virtual bool checkTransformValidity(T,T,T);

        protected:
            // Finding field generator
            static bool isGenerator(T, T, T, const std::list<T>&);
            static T findGenerator(T,T);

            // Validity checks
            inline bool isNthRootOfPrime(T,T,size_t);


            // Pad the input to desired length with zeroes
            template<typename G>
            inline G zeroPad(G&, size_t);

            // Transforms implementations
            template<typename G> G fastNtt(const G&, T);
            template<typename G> G naiveNtt(const G&);
            template<typename G> G fastIntt(const G&);
            template<typename G> G naiveIntt(const G&);

        public:
            //Constructor from parameters
            NumberTheoreticTransform(size_t,T);
            NumberTheoreticTransform(T,T,size_t);

            //Constructor from container
            template<typename G>
            explicit NumberTheoreticTransform(const G&, T = 0, T = 0);

            // Two way transform methods
            template<typename G>
            G transform(G);

            template<typename G>
            G inverseTransform(G);

            // Parameters' getters
            inline T getOmega();
            inline T getModulus();

            // Does this transform return a convolutable result
            constexpr bool isConvolutable();
        };

        template<typename T>
        using NTT = NumberTheoreticTransform<T>;
    }
}

#endif //BIGINTEGER_NUMBERTHEORETICTRANSFORM_HH
