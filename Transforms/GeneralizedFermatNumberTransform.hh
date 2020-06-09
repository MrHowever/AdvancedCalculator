//
// Created by mrhowever on 20.11.19.
//

#ifndef BIGINTEGER_GENERALIZEDFERMATNUMBERTRANSFORM_HH
#define BIGINTEGER_GENERALIZEDFERMATNUMBERTRANSFORM_HH

#include <cstddef>
#include "NumberTheoreticTransform.hh"

namespace MC {
    namespace MT {
        template <typename T>
        class GeneralizedFermatNumberTransform : public NumberTheoreticTransform<T>
        {
            inline T generateModulus(size_t,T);
            bool checkTransformValidity(T,T,T);

        public:
            //Constructor from parameters
            GeneralizedFermatNumberTransform(size_t,T);
            GeneralizedFermatNumberTransform(T,T,size_t);

            //Constructor from container
            template<typename G>
            explicit GeneralizedFermatNumberTransform(const G&);
        };

        template<typename T>
        using GFNT = GeneralizedFermatNumberTransform<T>;
    }
}


#endif //BIGINTEGER_GENERALIZEDFERMATNUMBERTRANSFORM_HH
