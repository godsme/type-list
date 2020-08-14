//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_RESERVE_H
#define TYPE_LIST_RESERVE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/Value.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename TL, typename ... Ts>
    struct Reverse {
        using type = TL;
    };

    template<typename TL, typename H, typename ... Ts>
    struct Reverse<TL, H, Ts...> {
        using type = typename Reverse<typename TL::template prependType<H>, Ts...>::type;
    };
}

template<typename FROM>
struct Reverse {
    template<typename ... Ts>
    using result = typename detail::Reverse<TypeList<>, Ts...>::type;

    using type = decltype(FROM::template exportTo<result>());
};

template<typename FROM>
using Reverse_t = typename Reverse<FROM>::type;

TYPE_LIST_NS_END

#define __TL_reverse(...) TYPE_LIST_NS::Reverse_t<__VA_ARGS__>

#endif //TYPE_LIST_RESERVE_H
