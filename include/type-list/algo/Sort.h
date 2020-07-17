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
#include <type-list/algo/Curry.h>
#include <type-list/algo/Bind.h>
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
        using result  = __TL_Partition(__TL_bind(LT, _1_, typename IN::Head), typename IN::Tail);
        using lesser  = __TL_apply_t(Sort, typename result::satisfied, LT);
        using greater = __TL_apply_t(Sort, typename result::rest, LT);
        __result_t(typename lesser::template appendType<typename IN::Head>::template appendList<greater>);
    };
}

namespace detail {
    template<typename LT, typename IN>
    struct SortType;

    template<TypeTemplateConcept LT, FiniteTypeListConcept IN>
    struct SortType<LT, IN> {
        using type = __TL_apply_t(Sort, IN, LT::template apply);
    };

    template<ValueTemplateConcept LT, FiniteValueListConcept IN>
    class SortType<LT, IN> {
        __TL_lambda(LessThan, typename T1, typename T2)
        __return_apply_v(LT::template apply, T1::value, T2::value);
    public:
        using type = __TL_apply_t(Sort, List<IN>, LessThan);
    };

    template<ValueConcept LT, FiniteValueListConcept IN>
    class SortType<LT, IN> {
        __TL_lambda(LessThan, typename T1, typename T2)
        __return_v(LT::value(T1::value, T2::value));
    public:
        using type = __TL_apply_t(Sort, List<IN>, LessThan);
    };
}

template<typename PRED, typename IN>
using Sort_t = typename detail::SortType<PRED, IN>::type;

namespace detail {
    template<typename T>
    concept IsEmptyList = std::is_same_v<EmptyList, T>;

    template<typename T>
    concept NonEmptyFiniteValueList = FiniteValueListConcept<T> && (!IsEmptyList<T>);

    template<typename T>
    concept NonEmptyFiniteTypeList = FiniteTypeListConcept<T> && (!IsEmptyList<T>);

    template<__TL_lambda(LT, typename, typename), NonEmptyFiniteTypeList IN>
    auto DeduceSortType() -> Sort_t<__TL_toType(LT), IN>;

    template<__TL_lambda(LT, auto, auto), NonEmptyFiniteValueList IN>
    auto DeduceSortType() -> Sort_t<__TL_toType(LT), IN>;

    template<auto LT, NonEmptyFiniteValueList IN>
    auto DeduceSortType() -> Sort_t<__TL_toType(LT), IN>;

    template<__TL_lambda(LT, typename, typename), IsEmptyList IN>
    auto DeduceSortType() -> EmptyList;

    template<__TL_lambda(LT, auto, auto), IsEmptyList IN>
    auto DeduceSortType() -> EmptyList;

    template<auto LT, IsEmptyList IN>
    auto DeduceSortType() -> EmptyList;
}

TYPE_LIST_NS_END

#define __TL_Sort(...) \
decltype(TYPE_LIST_NS::detail::DeduceSortType<__VA_ARGS__>())

#endif //TYPE_LIST_SORT_H
