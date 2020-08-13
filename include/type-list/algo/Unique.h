//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_UNIQUE_H
#define TYPE_LIST_UNIQUE_H

#include <type-list/type-list-ns.h>
#include <type-list/algo/Elem.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename TL, typename = void, typename ... Ts>
    struct Unique {
        using type = TL;
    };

    template<typename TL, typename H, typename ... Ts>
    struct Unique<TL, std::enable_if_t<Elem_v<H, TL>>, H, Ts...> {
        using type = typename Unique<TL, void, Ts...>::type;
    };

    template<typename TL, typename H, typename ... Ts>
    struct Unique<TL, std::enable_if_t<!Elem_v<H, TL>>, H, Ts...> {
        using type = typename Unique<typename TL::template appendType<H>, void, Ts...>::type;
    };
}

template<typename ... Ts>
using Unique_t = typename detail::Unique<TypeList<>, void, Ts...>::type;

template<typename TL>
using Unique_tl = decltype(TL::template exportTo<Unique_t>());

TYPE_LIST_NS_END

#define __TL_unique(...) TYPE_LIST_NS::Unique_tl<__VA_ARGS__>

#endif //TYPE_LIST_UNIQUE_H
