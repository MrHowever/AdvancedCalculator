//
// Created by mrhowever on 08.11.19.
//

#ifndef BIGINTEGER_BOUNDED_HH
#define BIGINTEGER_BOUNDED_HH

namespace MC {
    template<typename T>
    class Bounded {
        static T max() {
            return T::max();
        }

        static T min() {
            return T::min();
        }
    };
}
#endif //BIGINTEGER_BOUNDED_HH
