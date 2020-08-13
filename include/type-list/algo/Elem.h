//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_ELEM_H
#define TYPE_LIST_ELEM_H

#include <type-list/type-list-ns.h>
#include <type-list/types/TypeList.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename T, typename = void, typename ... Ts>
    struct Elem {
        constexpr static bool value = false;
    };

    template<typename T, typename H, typename ... Ts>
    struct Elem<T, std::enable_if_t<std::is_same_v<T, H>>, H, Ts...> {
        constexpr static bool value = true;
    };

    template<typename T, typename H, typename ... Ts>
    struct Elem<T, std::enable_if_t<!std::is_same_v<T, H>>, H, Ts...> {
        constexpr static bool value = Elem<T, void, Ts...>::value;
    };
}


template<typename T, typename TL>
struct Elem {
private:
    template<typename ... Ts>
    using elem = detail::Elem<T, void, Ts...>;

    using type = decltype(TL::template exportTo<elem>());

public:
    constexpr static bool value = type::value;
};

template<typename T, typename TL>
constexpr bool Elem_v = Elem<T, TL>::value;

TYPE_LIST_NS_END

#endif //TYPE_LIST_ELEM_H
