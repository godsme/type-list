//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_EXCEPT_H
#define TYPE_LIST_EXCEPT_H

#include <type-list/type-list-ns.h>
#include <type-list/algo/Elem.h>
#include <type-list/types/List.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename OPT_OUT, typename RESULT, typename = void, typename ... Ts>
    struct Except {
        using type = RESULT;
    };

    template<typename OPT_OUT, typename RESULT, typename H, typename ... Ts>
    struct Except<OPT_OUT, RESULT, std::enable_if_t<__TL_elem(H, OPT_OUT)>, H, Ts...> {
        using type = typename Except<OPT_OUT, RESULT, void, Ts...>::type;
    };

    template<typename OPT_OUT, typename RESULT, typename H, typename ... Ts>
    struct Except<OPT_OUT, RESULT, std::enable_if_t<!__TL_elem(H, OPT_OUT)>, H, Ts...> {
        using type = typename Except<OPT_OUT, typename RESULT::template appendType<H>, void, Ts...>::type;
    };
}

template<typename OPT_OUT, typename ALL>
struct Except {
    template<typename ... Ts>
    using f = typename detail::Except<OPT_OUT, TypeList<>, void, Ts...>::type;

    using type = decltype(ALL::template exportTo<f>());
};

template<typename OPT_OUT, typename ALL>
using Except_t = typename Except<OPT_OUT, ALL>::type;

TYPE_LIST_NS_END

#define __TL_except(...) TYPE_LIST_NS::Except_t<__VA_ARGS__>

#endif //TYPE_LIST_EXCEPT_H
