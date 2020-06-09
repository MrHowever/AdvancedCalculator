//
// Created by mrhowever on 18.10.19.
//

#include "BigInteger.hh"
#include <math.h>
#include <sstream>

//TODO what is the biggest possible base?

BigInteger::Base::Base(const BigInteger& integer, int base) : B(base)
{
    std::vector<int> baseDigits = add(separateDigits(integer.DIGIT_MAX), std::vector<int>() = {1});
    _baseDigits = separateDigits(integer._digits[0]);

    for(int i = 1; i < integer._digits.size(); i++) {
        std::vector<int> power = { 1 };

        for(int j = 0; j < i; j++) {
            power = multiplicate(power,baseDigits);
        }

        _baseDigits = add(_baseDigits, multiplicate(power,separateDigits(integer._digits[i])));
    }
}

std::vector<int> BigInteger::Base::separateDigits(uint64_t integer)
{
    std::vector<int> digits;

    if(integer == 0) {
        digits.push_back(0);
        return digits;
    }

    while(integer != 0) {
        digits.push_back(integer % B);
        integer /= B;
    }

    return digits;
}

std::vector<int> BigInteger::Base::add(std::vector<int> first, std::vector<int> second)
{
    int longerSize = std::max(first.size(), second.size());
    std::vector<int> result(longerSize);
    int overflow = 0;

    std::fill(result.begin(), result.end(),0);

    for(int i = 0; i < longerSize; i++) {
        result[i] += i < first.size() ? first[i] : 0;
        result[i] += i < second.size() ? second[i] : 0;
        result[i] += overflow;

        if(result[i] >= B) {
            overflow = 1;
            result[i] %= B;
        }
        else {
            overflow = 0;
        }
    }

    if(overflow) {
        result.push_back(1);
    }

    return result;
}

std::vector<int> BigInteger::Base::multiplicate(std::vector<int> first, std::vector<int> second)
{
    std::vector<int> result;

    for(int i = 0; i < second.size(); i++) {
        for(int j = 0; j < first.size(); j++) {
            if(result.size() == (i+j)) {
                result.push_back(0);
            }

            int value = second[i] * first[j];
            result[i+j] += value;
        }
    }

    int overflow = 0;

    for(int i = 0; i < result.size(); i++) {
        result[i] += overflow;

        if(result[i] >= B) {
            overflow = result[i] / B;
            result[i] %= B;
        }
        else {
            overflow = 0;
        }
    }

    if(overflow)
        result.push_back(overflow);

    return result;
}

std::string BigInteger::Base::toString()
{
    std::stringstream result;

    for(int i = _baseDigits.size() - 1; i >= 0; i--) {
        result << (_baseDigits[i] > 9 ? ((char) _baseDigits[i] + 55) : _baseDigits[i]);
    }

    return result.str();
}