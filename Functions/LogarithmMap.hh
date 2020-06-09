//
// Created by mrhowever on 12.02.2020.
//

#ifndef FUNCTIONS_LOGARITHMMAP_HH
#define FUNCTIONS_LOGARITHMMAP_HH

#include <map>
#include "ArithmeticObject.hh"
#include "Typedef.hh"

namespace MC::FN
{
    template<typename T>
    struct LogarithmMap {
        std::map<ArithmeticObject*,T> _map;

    public:
        LogarithmMap()                               = default;
        LogarithmMap(const LogarithmMap&);
        LogarithmMap& operator=(const LogarithmMap&);

        auto begin() const;
        auto end() const;
        auto size() const;

        void add(const Logarithm& log);
        T get(const OperandPtr&) const;
    };
}

#endif //FUNCTIONS_LOGARITHMMAP_HH