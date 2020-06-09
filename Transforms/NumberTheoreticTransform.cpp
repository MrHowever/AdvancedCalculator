//
// Created by mrhowever on 18.11.19.
//

#include <cmath>
#include <iostream>
#include "NumberTheoreticTransform.hh"
#include "../ModularOperations/ModularOperations.hh"
#include "../IntegerFactorization/PrimeFactorization.hh"
#include "TransformException.hh"


// TODO Check for possible overflows

template<typename T>
bool MC::MT::NumberTheoreticTransform<T>::isGenerator(T value, T totient, T modulus, const std::list<T>& primeFactors)
{
    for(auto factor : primeFactors) {
        if(MO::modularPow(value, totient / factor, modulus) == 1)
            return false;
    }

    return true;
}

//TODO swap input in FNT and MNT from T to FermatNumber and MersenneNumber

template<typename T>
T MC::MT::NumberTheoreticTransform<T>::findGenerator(T modulus, T totient)
{
    std::list<T> primeFactors = PF::naivePrimeFactorization(totient);

    for(T i = 1; i < modulus; i++) {
        if(isGenerator(i,totient,modulus,primeFactors))
            return i;
    }

    throw TransformException("No field generator found for given pair of modulus = " + std::to_string(modulus) + ", totient = " + std::to_string(totient));
}

template<typename T>
inline T MC::MT::NumberTheoreticTransform<T>::generateOmega(size_t transformLength, T modulus)
{
    return MO::modularPow(findGenerator(modulus, modulus-1), (modulus - 1) / transformLength, modulus);
}

template<typename T>
inline T MC::MT::NumberTheoreticTransform<T>::generateModulus(size_t transformLength, T maxElement)
{
    T minimumModulus = BO::max(maxElement,transformLength) + 1;
    T minimumK = (minimumModulus - 1) / transformLength;

    for(T k = minimumK; k < BO::max<T>(); k++) {
        T modulusCandidate = k*transformLength + 1;
        if(Prime<T>::isPrime(modulusCandidate)) {
            _k = k;     //TODO all the values are returned first except k, fix pls
            return modulusCandidate;
        }
    }

    throw TransformException("No fitting modulus found for the transform");
}

template<typename T>
inline size_t MC::MT::NumberTheoreticTransform<T>::calculateNMax(T modulus)
{
    auto primeFactors = PF::naivePrimeFactorization(modulus);
    std::transform(primeFactors.begin(),primeFactors.end(),primeFactors.begin(), //TODO loop?
                   [](auto e) { return e-1; });
    return BO::gcd(primeFactors);
}

template<typename T>
inline bool MC::MT::NumberTheoreticTransform<T>::isNthRootOfPrime(T omega, T modulus, size_t transformLength)
{
    return MO::modularPow(omega,transformLength,modulus) == 1;
}

template<typename T>
MC::MT::NumberTheoreticTransform<T>::NumberTheoreticTransform(T omega, T modulus, size_t transformLength)
{
    if(modulus <= 0)
        throw TransformException("Modulus in NTT must be positive");

    if(!checkTransformValidity(omega,modulus,transformLength)) {
        throw TransformException("NTT with parameters (omega,M) = ("+std::to_string(_omega)+","+std::to_string(_modulus)+") cannot be computed for this input length");
    }

    //                          If transform length isn't a power of 2
    if(NTT_AUTO_PADDING && !BO::isPowOf2(transformLength)) {
        _transformLength = std::round(std::pow(2,std::ceil(std::log2(transformLength))));
        _fft = true;
    }
    else {
        _transformLength = transformLength;
        _fft = BO::isPowOf2(transformLength);
    }
    
    _modulus = modulus;
    _omega = omega;
    _maxN = calculateNMax(modulus);
}

template<typename T>
MC::MT::NumberTheoreticTransform<T>::NumberTheoreticTransform(size_t transformLength, T maxElement)
{
    if(_modulus <= 0)
        throw TransformException("Modulus in NTT must be positive");
    
//                          If transform length isn't a power of 2
    if(NTT_AUTO_PADDING && !BO::isPowOf2(transformLength)) {
        _transformLength = std::round(std::pow(2,std::ceil(std::log2(transformLength))));
        _fft = true;
    }
    else {
        _transformLength = transformLength;
        _fft = BO::isPowOf2(transformLength);
    }
    
    _modulus = generateModulus(transformLength,maxElement);
    _omega = generateOmega(transformLength,_modulus);

    if(!checkTransformValidity(_omega,_modulus, _transformLength)) {
        throw TransformException("NTT with parameters (omega,M) = ("+std::to_string(_omega)+","+std::to_string(_modulus)+") cannot be computed for this input length");
    }
    
    _maxN = calculateNMax(_modulus);
}

template<typename T>
template<typename G>
MC::MT::NumberTheoreticTransform<T>::NumberTheoreticTransform(const G& container, T omega, T modulus)
{
    if constexpr (MC::is_container<G>::value) {
        if (_modulus <= 0)
            throw TransformException("Modulus in NTT must be positive");

        //                          If transform length isn't a power of 2
        if(NTT_AUTO_PADDING && !BO::isPowOf2(container.size())) {
            _transformLength = std::round(std::pow(2,std::ceil(std::log2(container.size()))));
            _fft = true;
        }
        else {
            _transformLength = container.size();
            _fft = BO::isPowOf2(container.size());
        }
        
        _modulus = modulus ? modulus : generateModulus(_transformLength, BO::max(container));
        _omega = omega ? omega : generateOmega(_transformLength, _modulus);

        std::cout<<"xd"<<std::endl;

        if (!checkTransformValidity(_omega, _modulus, _transformLength)) {
            throw TransformException("NTT with parameters (omega,M) = (" + std::to_string(_omega) + "," + std::to_string(_modulus)
                                                                         + ") cannot be computed for this input length");
        }

        _maxN = calculateNMax(_modulus);
    }
    else {
        throw TransformException("Transform constructor for containers used with a non-container type");
    }
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::transform(G input)
{
    if constexpr(MC::is_container<G>::value) {
        if(input.size() != _transformLength) {
            if(NTT_AUTO_PADDING) {
                zeroPad(input,_transformLength);
            }
            else {
                throw TransformException("Invalid input length for this transform. With automatic zero-padding disabled input length must be equal to transformLength");
            }
        }

        if(_fft)
            return fastNtt(input, _omega);
        else
            return naiveNtt(input);

    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::inverseTransform(G input)
{
    if constexpr(MC::is_container<G>::value) {
        if(input.size() != _transformLength) {
            throw TransformException("This sequence was not a result of this transform because the transforms lengths do not match");
        }

        //TODO check for max value in input > _modulus?

        if(_fft)
            return fastIntt(input);
        else
            return naiveIntt(input);
    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
bool MC::MT::NumberTheoreticTransform<T>::checkTransformValidity(T omega, T modulus, T transformLength)
{
    if(modulus <= 0 || transformLength <= 0 || omega == 0)
        return false;

    return isNthRootOfPrime(omega,modulus,transformLength);
}

template<typename T>
template<typename G>
inline G MC::MT::NumberTheoreticTransform<T>::zeroPad(G& input, size_t newSize)
{
    input.insert(input.end(), newSize - input.size(), 0);
    return input;
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::fastNtt(const G& input, T omega)
{
    if constexpr(MC::is_container<G>::value) {
        if constexpr (NTT_SAFETY_CHECKS) {
            if(!BO::isPowOf2(input.size()))
                throw TransformException("Implementation error. Fast NTT called with input length not a power of 2");

            //TODO
//     if(input.size() != _transformLength)
  //              throw TransformException("This input has different length than transform length and hasn't been zero padded");
        }

        size_t halfSize = input.size() >> 1;

        if(input.size() == 1)
            return input;

        G even(halfSize), odd(halfSize);

        auto evenIter = even.begin();
        auto oddIter = odd.begin();
        for(uint i = 0; i < input.size(); i++) {
            (i & 1u ? *(oddIter++) : *(evenIter++) ) = input[i];
        }

        even = fastNtt(even, MO::modularPow<T>(omega, 2, _modulus));
        odd = fastNtt(odd, MO::modularPow<T>(omega, 2, _modulus));

        G result(input.size());

        for(int i = 0; i < halfSize; i++) {
            T prod = MO::modularMult<T>(MO::modularPow<T>(omega,i,_modulus),odd[i],_modulus);
            result[i] = MO::modularAdd(even[i],prod,_modulus);
            result[i + halfSize] = MO::modularSub(even[i],prod,_modulus);
        }

        return result;
    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::fastIntt(const G& input)
{
    if constexpr(MC::is_container<G>::value) {
        if constexpr (NTT_SAFETY_CHECKS) {
            if(!BO::isPowOf2(input.size()))
                throw TransformException("Implementation error. Fast INTT called with input length not a power of 2");

            if(input.size() != _transformLength)
                throw TransformException("This input has different length than transform length and hasn't been zero padded");
        }

        G result(input);
        result = fastNtt(result,MO::reciprocal<T>(_omega,_modulus));

        //TODO check if for loop wont be faster
        std::transform(result.begin(),result.end(),result.begin(),
                       [&result, this](auto e){ return MO::modularMult(e,MO::reciprocal<T>(result.size(),_modulus),_modulus);});

        return result;

    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::naiveNtt(const G& input)
{
    if constexpr(MC::is_container<G>::value) {
        if constexpr (NTT_SAFETY_CHECKS) {
            if(input.size() != _transformLength)
                throw TransformException("This input has different length than transform length and hasn't been zero padded");
        }

        G result(_transformLength);

        size_t outIdx = 0, inIdx = 0;
        for(auto& outElem : result) {
            for(auto& inElem : input) {
                //TODO outIdx * inIdx might overflow in edge cases and it cannot be multiplied under modulo
                outElem = MO::modularAdd(outElem, MO::modularMult(inElem, MO::modularPow(_omega, outIdx * inIdx, _modulus), _modulus), _modulus);
            }

            outIdx++;
            inIdx = 0;
        }

        return result;
    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
template<typename G>
G MC::MT::NumberTheoreticTransform<T>::naiveIntt(const G& input)
{
    if constexpr(MC::is_container<G>::value) {
        if constexpr (NTT_SAFETY_CHECKS) {
            if(input.size() != _transformLength)
                throw TransformException("This input has different length than transform length and hasn't been zero padded");
        }

        G result(_transformLength);

        size_t outIdx = 0, inIdx = 0;
        for(auto& outElem : result) {
            for(auto& inElem : input) {
                //TODO outIdx * inIdx might overflow in edge cases and it cannot be multiplied under modulo, here additionaly it has to be signed value because of -1
                outElem = MO::modularAdd(outElem, MO::modularMult(inElem, MO::modularPow(_omega, -1 * outIdx * inIdx, _modulus), _modulus), _modulus);
            }

            outElem = MO::modularMult(outElem, MO::reciprocal<T>(_transformLength, _modulus), _modulus);

            outIdx++;
            inIdx = 0;
        }

        return result;
    }
    else
        throw TransformException("Only containers of values can be transformed");
}

template<typename T>
constexpr bool MC::MT::NumberTheoreticTransform<T>::isConvolutable()
{
    return _transformLength < _maxN;
}

template<typename T>
inline T MC::MT::NumberTheoreticTransform<T>::getOmega()
{
    return _omega;
}

template<typename T>
inline T MC::MT::NumberTheoreticTransform<T>::getModulus()
{
    return _modulus;
}