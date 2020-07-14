//
// Created by godsme on 7/14/20.
//

#ifndef TYPE_LIST_SORT_H
#define TYPE_LIST_SORT_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/algo/Filter.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Sort,
            FiniteListConcept IN,
            __TL_lambda(LT, typename, typename))
    __return_t(__TL_list());

    __TL_lambda(Sort,
            NonEmptyFiniteListConcept IN,
            __TL_lambda(LT, typename, typename))
    <IN, LT> {
        __TL_lambda(LessThan, typename T) __return_apply_v(LT, T, typename IN::Head);
        using result  = __TL_filter(typename IN::Tail, LessThan);
        using lesser  = __TL_apply_t(Sort, typename result::satisfied, LT);
        using greater = __TL_apply_t(Sort, typename result::rest, LT);
        __result_t(typename lesser::template appendType<typename IN::Head>::template appendList<greater>);
    };
}

template<FiniteTypeListConcept IN, __TL_lambda(LT, typename, typename)>
using Sort_t = __TL_apply_t(detail::Sort, IN, LT);

TYPE_LIST_NS_END

#define __TL_sort(...) TYPE_LIST_NS::Sort_t<__VA_ARGS__>

#endif //TYPE_LIST_SORT_H
