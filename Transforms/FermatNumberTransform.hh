//
// Created by mrhowever on 18.11.19.
//

#ifndef BIGINTEGER_FERMATNUMBERTRANSFORM_HH
#define BIGINTEGER_FERMATNUMBERTRANSFORM_HH


#include "NumberTheoreticTransform.hh"

//TODO constrain T to strictly integer types

namespace MC {
    namespace MT {
        template<typename T>
        class FermatNumberTransform : public NumberTheoreticTransform<T> {
            inline T generateModulus(size_t,T);
            bool checkTransformValidity(T,T,T);

        public:
            //Constructor from parameters
            FermatNumberTransform(size_t,T);
            FermatNumberTransform(T,T,size_t);

            //Constructor from container
            template<typename G>
            explicit FermatNumberTransform(const G&);
        };

        template<typename T>
        using FNT = FermatNumberTransform<T>;
    }
}


#endif //BIGINTEGER_FERMATNUMBERTRANSFORM_HH
