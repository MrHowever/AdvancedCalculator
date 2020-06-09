//
// Created by mrhowever on 18.11.19.
//

#include "MersenneNumberTransform.hh"
#include <cmath>
#include "../BasicOperations/BasicOperations.hh"
#include "TransformException.hh"
#include "NumberTheoreticTransform.hh"
#include "../ArithmeticFunctions/ArithmeticFunctions.hh"

template<typename T>
inline T MC::MT::MersenneNumberTransform<T>::generateModulus(size_t transformLength, T maxElement)
{
    T lowerBound = BO::max(maxElement,transformLength) + 1;
    T power = std::ceil(std::log2(lowerBound));
    return AF::pow(AF::pow(2,2),power) - 1;
}

template<typename T>
bool MC::MT::MersenneNumberTransform<T>::checkTransformValidity(T omega, T modulus, T transformLength)
{
    if(modulus <= 0 || transformLength <= 0 || omega == 0)
        return false;

    //TODO technically std::round and log2 might not return perfect integer for HUGE power of 2 (big 64-bit integers )
    if(!BO::isPowOf2(modulus + 1))
        return false;

    return isNthRootOfPrime(omega,modulus,transformLength);
}

template<typename T>
MC::MT::MersenneNumberTransform<T>::MersenneNumberTransform(T omega, T modulus, size_t transformLength)
{
    if(modulus <= 0)
        throw TransformException("Modulus in MNT must be positive");

    if(!checkTransformValidity(omega,modulus,transformLength)) {
        throw TransformException("MNT with parameters (omega,M) = ("+std::to_string(this->_omega)+","+std::to_string(this->_modulus)+") cannot be computed for this input length");
    }

    //                          If transform length isn't a power of 2
    if(NTT_AUTO_PADDING && !BO::isPowOf2(transformLength)) {
        this->_transformLength = std::round(std::pow(2,std::ceil(std::log2(transformLength))));
        this->_fft = true;
    }
    else {
        this->_transformLength = transformLength;
        this->_fft = BO::isPowOf2(transformLength);
    }

    this->_modulus = modulus;
    this->_omega = omega;
    this->_maxN = calculateNMax(modulus);
}

template<typename T>
MC::MT::MersenneNumberTransform<T>::MersenneNumberTransform(size_t transformLength, T maxElement)
{
    if(this->_modulus <= 0)
        throw TransformException("Modulus in MNT must be positive");

    this->_transformLength = transformLength;
    this->_modulus = generateModulus(transformLength,maxElement);
    this->_omega = generateOmega(transformLength,this->_modulus);

    if(!checkTransformValidity(this->_omega,this->_modulus,this->_transformLength)) {
        throw TransformException("MNT with parameters (omega,M) = ("+std::to_string(this->_omega)+","+std::to_string(this->_modulus)+") cannot be computed for this input length");
    }

    this->_maxN = calculateNMax(this->_modulus);
}

template<typename T>
template<typename G>
MC::MT::MersenneNumberTransform<T>::MersenneNumberTransform(const G& container)
{
    if constexpr (MC::is_container<G>::value) {
        if (this->_modulus <= 0)
            throw TransformException("Modulus in MNT must be positive");

        this->_transformLength = container.size();
        this->_modulus = generateModulus(this->_transformLength, BO::max(container));
        this->_omega = generateOmega(this->_transformLength, this->_modulus);

        if (!checkTransformValidity(this->_omega, this->_modulus, this->_transformLength)) {
            throw TransformException("MNT with parameters (omega,M) = (" + std::to_string(this->_omega) + "," + std::to_string(this->_modulus)
                                                                         + ") cannot be computed for this input length");
        }

        this->_maxN = calculateNMax(this->_modulus);
    }
    else {
        throw TransformException("Transform constructor for containers used with a non-container type");
    }
}