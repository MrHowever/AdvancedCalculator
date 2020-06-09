cmake_minimum_required(VERSION 3.14)
project(BigInteger)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES BigInteger.cpp BigIntegerComparisons.cpp BigIntegerBitwiseOperations.cpp BigIntegerArithmeticOperations.cpp BigIntegerUtilities.cpp FourierTransform.cpp FourierTransform.hh ../Prime/Prime.cpp ../Prime/Prime.hh ../Random/Random.cpp ../Random/Random.hh ../Random/Randomizable.hh ../Random/Randomizable.hh ../Interfaces/Bounded.hh ../Random/RandomizerException.hh ../Prime/PrimeException.hh ../ModularOperations/ModularOperations/ModularOperations.hh ../BasicOperations/BasicOperations/BasicOperations.hh ../BasicOperations/BasicOperations/BasicOperationsException.hh ../Interfaces/Comparable.hh ../TypeTraits/CustomTypeTraits.hh ../Totients/Totients.hh ../IntegerFactorization/PrimeFactorization.hh ../ArithmeticFunctions/ArithmeticFunctions.hh ../Interfaces/BitShiftable.hh ../Transforms/FourierTransform.cpp ../Transforms/FourierTransform.hh ../Transforms/DiscreteFourierTransform.cpp ../Transforms/DiscreteFourierTransform.hh ../Transforms/NumberTheoreticTransform.cpp ../Transforms/NumberTheoreticTransform.hh ../Transforms/FermatNumberTransform.cpp ../Transforms/FermatNumberTransform.hh ../Transforms/MersenneNumberTransform.cpp ../Transforms/MersenneNumberTransform.hh ../Transforms/TransformException.hh ../Transforms/GeneralizedFermatNumberTransform.cpp ../Transforms/GeneralizedFermatNumberTransform.hh ../SpecialNumbers/MersenneNumber.cpp ../SpecialNumbers/MersenneNumber.hh ../SpecialNumbers/InvalidParameterException.hh ../SpecialNumbers/FermatNumber.cpp ../SpecialNumbers/FermatNumber.hh)

add_subdirectory(Tests)

add_library(BigInteger ${SOURCE_FILES})
