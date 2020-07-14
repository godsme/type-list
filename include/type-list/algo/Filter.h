//
// Created by godsme on 7/14/20.
//

#ifndef TYPE_LIST_FILTER_H
#define TYPE_LIST_FILTER_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/ListWrapper.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Filter,
                FiniteListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED = TypeList<>,
                ListConcept REST = TypeList<>,
                typename = void)
        __return_t(struct {
               using satisfied = __TL_apply_t(detail::EmptyListTrait, SATISFIED);
               using rest      = __TL_apply_t(detail::EmptyListTrait, REST);
           });

    __TL_lambda(Filter,
                FiniteTypeListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED,
                ListConcept REST)
    <IN, PRED, SATISFIED, REST, std::enable_if_t<__TL_apply_v(PRED, typename IN::Head)>>
        __return_apply_t(Filter
            , typename IN::Tail
            , PRED
            , typename SATISFIED::template appendType<typename IN::Head>
            , REST);

    __TL_lambda(Filter,
                FiniteTypeListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED,
                ListConcept REST)
    <IN, PRED, SATISFIED, REST, std::enable_if_t<!__TL_apply_v(PRED, typename IN::Head)>>
        __return_apply_t(Filter
            , typename IN::Tail
            , PRED
            , SATISFIED
            , typename REST::template appendType<typename IN::Head>);
}

namespace detail {
    template<__TL_lambda(PRED, auto)>
    struct ValuePredAdapter {
        __TL_lambda(Pred, typename T) __return_apply_v(PRED, T::value);
    };
}

template<FiniteValueListConcept IN, __TL_lambda(PRED, auto)>
using FilterValue_t =
        __TL_apply_t(detail::Filter,
            List<IN>,
            detail::ValuePredAdapter<PRED>::template Pred,
            ValueList<>,
            ValueList<>);

namespace detail {
    template<auto F>
    struct PredFuncAdapter {
        __TL_lambda(Pred, typename T) __return_v(F(T::value));
    };
}

template<FiniteValueListConcept IN, auto PRED>
using FilterValueF_t =
        __TL_apply_t(detail::Filter,
               List<IN>,
               detail::PredFuncAdapter<PRED>::template Pred,
               ValueList<>,
               ValueList<>);

template<FiniteTypeListConcept IN, __TL_lambda(PRED, typename)>
using Filter_t = __TL_apply_t(detail::Filter, IN, PRED, TypeList<>, TypeList<>);

namespace detail {
    template<typename IN, __TL_lambda(PRED, __Set())>
    requires (FiniteTypeListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeductFilter() -> Filter_t<IN, PRED>;

    template<typename IN, __TL_lambda(PRED, auto)>
    requires (FiniteValueListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeductFilter() -> FilterValue_t<IN, PRED>;

    template<typename IN, auto PRED>
    requires (FiniteValueListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeductFilter() -> FilterValueF_t<IN, PRED>;

    template<typename IN, __TL_lambda(PRED, __Set())>
    requires std::is_same_v<EmptyList, IN>
    auto DeductFilter() -> __TL_apply_t(detail::Filter, IN, PRED, EmptyList, EmptyList);

    template<typename IN, __TL_lambda(PRED, auto)>
    requires std::is_same_v<EmptyList, IN>
    auto DeductFilter() -> __TL_apply_t(detail::Filter, IN, ValuePredAdapter<PRED>::template Pred, EmptyList, EmptyList);

    template<typename IN, auto PRED>
    requires std::is_same_v<EmptyList, IN>
    auto DeductFilter() -> __TL_apply_t(detail::Filter, IN, PredFuncAdapter<PRED>::template Pred, EmptyList, EmptyList);
}

TYPE_LIST_NS_END

#define __TL_filter(in, f) \
decltype(TYPE_LIST_NS::detail::DeductFilter<in, f>())

#endif //TYPE_LIST_FILTER_H
