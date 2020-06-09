//
// Created by mrhowever on 14.11.19.
//

#ifndef BIGINTEGER_TOTIENTS_HH
#define BIGINTEGER_TOTIENTS_HH

namespace MC
{
    namespace TO
    {
        template<typename T>
        T eulerPhi(T value)
        {
            T result = value;

            for(int i = 2; (i*i) <= value; i++) {
                if(value % i == 0) {
                    while(value % i == 0) {
                        value /= i;
                    }

                    result -= result / i;
                }
            }

            if(result > 1)
                result -= result / value;

            return result;
        }
    }
}

#endif //BIGINTEGER_TOTIENTS_HH
