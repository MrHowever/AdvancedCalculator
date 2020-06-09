//
// Created by mrhowever on 12.02.2020.
//

#ifndef FUNCTIONS_LOGARITHMMAP_TCC
#define FUNCTIONS_LOGARITHMMAP_TCC

#include "Value.hh"
#include "Logarithm.hh"
#include "Variable.hh"
#include "ArithmeticObject.hh"
#include "OperatorFactory.hh"
#include "Typedefs.hh"

namespace MC::FN
{
    template<typename T>
    LogarithmMap<T>::LogarithmMap(const LogarithmMap& lm) : _map()
    {
        for(auto& pair : lm._map) {
            _map.at(pair.first) = pair.second;
        }
    }

    template<typename T>
    LogarithmMap<T>& LogarithmMap<T>::operator=(const LogarithmMap& lm)
    {
        for(auto& pair : lm._map) {
            _map.at(pair.first) = pair.second;
        }

        return *this;
    }

    template<typename T>
    auto LogarithmMap<T>::begin() const
    {
        return _map.begin();
    }

    template<typename T>
    auto LogarithmMap<T>::end() const
    {
        return _map.end();
    }

    template<typename T>
    auto LogarithmMap<T>::size() const
    {
        return _map.size();
    }

    template<typename T>
    void LogarithmMap<T>::add(const Logarithm& log)
    {
        ArithmeticObject* base = const_cast<ArithmeticObject*>(log.getBase());

        if (_map.find(base) != _map.end()) {
            if constexpr(AreSameV<T, Logarithm>) {
                _map.at(base) = _map.at(base) + log;
            } else if constexpr(AreSameV<T,LogList>){
                _map.at(base).push_back(log);
            }
        } else {
            if constexpr(AreSameV<T, Logarithm>) {
                _map.at(base) = log;
            } else if constexpr(AreSameV<T,LogList>){
                _map.at(base) = LogList{ log };
            }
        }
    }

    template<typename T>
    T LogarithmMap<T>::get(const OperandPtr& base) const
    {
        return _map.at(base);
    }
}

#endif