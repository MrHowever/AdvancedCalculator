//
// Created by mrhowever on 13.11.19.
//

#ifndef BIGINTEGER_CUSTOMTYPETRAITS_HH
#define BIGINTEGER_CUSTOMTYPETRAITS_HH

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <type_traits>

namespace MC{
    template <typename T> struct is_container:std::false_type{};
    template <typename T, std::size_t N> struct is_container<std::array<T,N>>:std::true_type{};
    template <typename... Args> struct is_container<std::vector<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::deque<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::list<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::forward_list<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::set<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::multiset<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::map<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::multimap<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::unordered_set<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::unordered_multiset<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::unordered_map<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::unordered_multimap<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::stack<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::queue<Args...>>:std::true_type{};
    template <typename... Args> struct is_container<std::priority_queue<Args...>>:std::true_type{};
}

template <typename T> struct is_container {
    static constexpr bool const value = MC::is_container<std::decay_t<T>>::value;
};

namespace MC {
    template <typename T> struct is_short : std::false_type {};
    template<> struct is_short<int8_t>    : std::true_type  {};
    template<> struct is_short<uint8_t>   : std::true_type  {};
    template<> struct is_short<int16_t>   : std::true_type  {};
    template<> struct is_short<uint16_t>  : std::true_type  {};
}

template <typename T> struct is_short {
    static constexpr bool const value = MC::is_short<std::decay_t<T>>::value;
};

namespace MC {
    template <typename T, int Size> struct is_smaller : std::false_type {};
    template <> struct is_smaller<int8_t,16>          : std::true_type {};
    template <> struct is_smaller<uint8_t,16>         : std::true_type {};
    template <> struct is_smaller<int8_t,32>          : std::true_type {};
    template <> struct is_smaller<uint8_t,32>         : std::true_type {};
    template <> struct is_smaller<int16_t,32>         : std::true_type {};
    template <> struct is_smaller<uint16_t,32>        : std::true_type {};
    template <> struct is_smaller<int8_t,64>          : std::true_type {};
    template <> struct is_smaller<uint8_t,64>         : std::true_type {};
    template <> struct is_smaller<int16_t,64>         : std::true_type {};
    template <> struct is_smaller<uint16_t,64>        : std::true_type {};
    template <> struct is_smaller<int32_t,64>         : std::true_type {};
    template <> struct is_smaller<uint32_t,64>        : std::true_type {};
}

template <typename T, int Size> struct is_smaller {
    static constexpr bool const value = MC::is_smaller<std::decay_t<T>, Size>::value;
};
#endif //BIGINTEGER_CUSTOMTYPETRAITS_HH
