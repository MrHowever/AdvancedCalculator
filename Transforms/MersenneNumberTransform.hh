//
// Created by mrhowever on 18.11.19.
//

#ifndef BIGINTEGER_MERSENNENUMBERTRANSFORM_HH
#define BIGINTEGER_MERSENNENUMBERTRANSFORM_HH


#include "NumberTheoreticTransform.hh"

namespace MC {
    namespace MT {
        template<typename T>
        class MersenneNumberTransform : public NumberTheoreticTransform<T> {
            inline T generateModulus(size_t,T);
            bool checkTransformValidity(T,T,T);

        public:
            //Constructor from parameters
            MersenneNumberTransform(size_t,T);
            MersenneNumberTransform(T,T,size_t);

            //Constructor from container
            template<typename G>
            explicit MersenneNumberTransform(const G&);
        };

        template<typename T>
        using MNT = MersenneNumberTransform<T>;
    }
}


#endif //BIGINTEGER_MERSENNENUMBERTRANSFORM_HH
