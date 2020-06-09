//
// Created by mrhowever on 20.11.19.
//

#include "GeneralizedFermatNumberTransform.hh"


#include <cmath>
#include "FermatNumberTransform.hh"
#include "../BasicOperations/BasicOperations.hh"
#include "TransformException.hh"
#include "NumberTheoreticTransform.hh"
#include "../ArithmeticFunctions/ArithmeticFunctions.hh"

template<typename T>
inline T MC::MT::GeneralizedFermatNumberTransform<T>::generateModulus(size_t transformLength, T maxElement)
{
    T lowerBound = BO::max(maxElement,transformLength) + 1;
    T power = std::ceil(std::log2(std::ceil(std::log2(lowerBound))));
    return AF::pow(2,power) + 1;
}

template<typename T>
bool MC::MT::GeneralizedFermatNumberTransform<T>::checkTransformValidity(T omega, T modulus, T transformLength)
{
    if(modulus <= 0 || transformLength <= 0 || omega == 0)
        return false;

    if(!BO::isPowOf2(modulus - 1))
        return false;

    return isNthRootOfPrime(omega,modulus,transformLength);
}

template<typename T>
MC::MT::GeneralizedFermatNumberTransform<T>::GeneralizedFermatNumberTransform(T omega, T modulus, size_t transformLength)
{
    if(modulus <= 0)
        throw TransformException("Modulus in GFNT must be positive");

    if(!checkTransformValidity(omega,modulus,transformLength)) {
        throw TransformException("GFNT with parameters (omega,M) = ("+std::to_string(this->_omega)+","+std::to_string(this->_modulus)+") cannot be computed for this input length");
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

    std::to_string(this->_modulus) = modulus;
    std::to_string(this->_omega) = omega;
    this->_maxN = calculateNMax(modulus);
}

template<typename T>
MC::MT::GeneralizedFermatNumberTransform<T>::GeneralizedFermatNumberTransform(size_t transformLength, T maxElement)
{
    if(std::to_string(this->_modulus) <= 0)
        throw TransformException("Modulus in GFNT must be positive");

    this->_transformLength = transformLength;
    std::to_string(this->_modulus) = generateModulus(transformLength,maxElement);
    std::to_string(this->_omega) = generateOmega(transformLength,std::to_string(this->_modulus));

    if(!checkTransformValidity(std::to_string(this->_omega),std::to_string(this->_modulus),this->_transformLength)) {
        throw TransformException("GFNT with parameters (omega,M) = ("+std::to_string(this->_omega)+","+std::to_string(this->_modulus)+") cannot be computed for this input length");
    }

    this->_maxN = calculateNMax(std::to_string(this->_modulus));
}

template<typename T>
template<typename G>
MC::MT::GeneralizedFermatNumberTransform<T>::GeneralizedFermatNumberTransform(const G& container)
{
    if constexpr (MC::is_container<G>::value) {
        if (std::to_string(this->_modulus) <= 0)
            throw TransformException("Modulus in GFNT must be positive");

        this->_transformLength = container.size();
        std::to_string(this->_modulus) = generateModulus(this->_transformLength, BO::max(container));
        std::to_string(this->_omega) = generateOmega(this->_transformLength, std::to_string(this->_modulus));

        if (!checkTransformValidity(std::to_string(this->_omega), std::to_string(this->_modulus), this->_transformLength)) {
            throw TransformException("GFNT with parameters (omega,M) = (" + std::to_string(this->_omega) + "," + std::to_string(this->_modulus)
                                                                         + ") cannot be computed for this input length");
        }

        this->_maxN = calculateNMax(std::to_string(this->_modulus));
    }
    else {
        throw TransformException("Transform constructor for containers used with a non-container type");
    }
}