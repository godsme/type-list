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

namespace detail {
    template<__TL_lambda(Compare, auto, auto)>
    struct ValueCompareAdapter {
        __TL_lambda(LessThan, typename T1, typename T2)
            __return_apply_v(Compare, T1::value, T2::value);
    };
}

template<FiniteValueListConcept IN, __TL_lambda(LT, auto, auto)>
using SortValue_t = __TL_apply_t(detail::Sort,
        List<IN>,
        detail::ValueCompareAdapter<LT>::template LessThan);

namespace detail {
    template<auto LT>
    struct CompareFuncAdapter {
        __TL_lambda(LessThan, typename T1, typename T2)
        __return_v(LT(T1::value, T2::value));
    };
}

template<FiniteValueListConcept IN, auto LT>
using SortValueF_t =
        __TL_apply_t(detail::Sort,
              List<IN>,
              detail::CompareFuncAdapter<LT>::template LessThan);

namespace detail {
    template<typename T>
    concept IsEmptyList = std::is_same_v<EmptyList, T>;

    template<typename IN, __TL_lambda(LT, typename, typename)>
    requires FiniteTypeListConcept<IN> && (!IsEmptyList<IN>)
    auto DeduceSortType() -> Sort_t<IN, LT>;

    template<typename IN, __TL_lambda(LT, auto, auto)>
    requires FiniteValueListConcept<IN> && (!IsEmptyList<IN>)
    auto DeduceSortType() -> SortValue_t<IN, LT>;

    template<typename IN, auto LT>
    requires FiniteValueListConcept<IN> && (!IsEmptyList<IN>)
    auto DeduceSortType() -> SortValueF_t<IN, LT>;

    template<IsEmptyList IN, __TL_lambda(LT, typename, typename)>
    auto DeduceSortType() -> EmptyList;

    template<IsEmptyList IN, __TL_lambda(LT, auto, auto)>
    auto DeduceSortType() -> EmptyList;

    template<IsEmptyList IN, auto LT>
    auto DeduceSortType() -> EmptyList;
}

TYPE_LIST_NS_END

#define __TL_sort(...) \
decltype(TYPE_LIST_NS::detail::DeduceSortType<__VA_ARGS__>())

#endif //TYPE_LIST_SORT_H
