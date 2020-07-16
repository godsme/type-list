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
    __TL_lambda(Partition,
                FiniteListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED = TypeList<>,
                ListConcept REST = TypeList<>,
                typename = void)
        __return_t(struct {
               using satisfied = __TL_apply_t(detail::EmptyListTrait, SATISFIED);
               using rest      = __TL_apply_t(detail::EmptyListTrait, REST);
           });

    __TL_lambda(Partition,
                FiniteTypeListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED,
                ListConcept REST)
    <IN, PRED, SATISFIED, REST, std::enable_if_t<__TL_apply_v(PRED, typename IN::Head)>>
        __return_apply_t(Partition
            , typename IN::Tail
            , PRED
            , typename SATISFIED::template appendType<typename IN::Head>
            , REST);

    __TL_lambda(Partition,
                FiniteTypeListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED,
                ListConcept REST)
    <IN, PRED, SATISFIED, REST, std::enable_if_t<!__TL_apply_v(PRED, typename IN::Head)>>
        __return_apply_t(Partition
            , typename IN::Tail
            , PRED
            , SATISFIED
            , __TL_scope_apply(REST, appendType, typename IN::Head));
}

namespace detail {
    template<__TL_lambda(PRED, auto)>
    struct ValuePredAdapter {
        __TL_lambda(Pred, typename T) __return_apply_v(PRED, T::value);
    };
}

template<FiniteValueListConcept IN, __TL_lambda(PRED, auto)>
using PartitionValue_t =
        __TL_apply_t(detail::Partition,
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
using PartitionValueF_t =
        __TL_apply_t(detail::Partition,
               List<IN>,
               detail::PredFuncAdapter<PRED>::template Pred,
               ValueList<>,
               ValueList<>);

template<FiniteTypeListConcept IN, __TL_lambda(PRED, typename)>
using Partition_t = __TL_apply_t(detail::Partition, IN, PRED, TypeList<>, TypeList<>);

namespace detail {
    template<typename IN, __TL_lambda(PRED, __Set())>
    requires (FiniteTypeListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeducePartition() -> Partition_t<IN, PRED>;

    template<typename IN, __TL_lambda(PRED, auto)>
    requires (FiniteValueListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeducePartition() -> PartitionValue_t<IN, PRED>;

    template<typename IN, auto PRED>
    requires (FiniteValueListConcept<IN> && !std::is_same_v<EmptyList, IN>)
    auto DeducePartition() -> PartitionValueF_t<IN, PRED>;

    template<typename IN, __TL_lambda(PRED, __Set())>
    requires std::is_same_v<EmptyList, IN>
    auto DeducePartition() -> __TL_apply_t(detail::Partition, IN, PRED, EmptyList, EmptyList);

    template<typename IN, __TL_lambda(PRED, auto)>
    requires std::is_same_v<EmptyList, IN>
    auto DeducePartition() -> __TL_apply_t(detail::Partition, IN, ValuePredAdapter<PRED>::template Pred, EmptyList, EmptyList);

    template<typename IN, auto PRED>
    requires std::is_same_v<EmptyList, IN>
    auto DeducePartition() -> __TL_apply_t(detail::Partition, IN, PredFuncAdapter<PRED>::template Pred, EmptyList, EmptyList);
}

#define __TL_partition(in, f) \
decltype(TYPE_LIST_NS::detail::DeducePartition<in, f>())

#define __TL_Filter(in, f) typename __TL_partition(in, f)::satisfied

namespace detail {
    __TL_lambda(FilterType_P, __TL_lambda(PRED, typename))
    __return_lambda_t(__TL_params(typename IN), __TL_Filter(IN, PRED));

    __TL_lambda(FilterValue_P, __TL_lambda(PRED, auto))
    __return_lambda_t(__TL_params(typename IN), __TL_Filter(IN, PRED));

    __TL_lambda(FilterValueF_P, auto PRED)
    __return_lambda_t(__TL_params(typename IN), __TL_Filter(IN, PRED));

    template<__TL_lambda(PRED, __Set())>
    auto DeduceFilter() -> FilterType_P<PRED>;

    template<__TL_lambda(PRED, auto)>
    auto DeduceFilter() -> FilterValue_P<PRED>;

    template<auto PRED>
    auto DeduceFilter() -> FilterValueF_P<PRED>;
}

TYPE_LIST_NS_END

#define __TL_filter(...) \
decltype(TYPE_LIST_NS::detail::DeduceFilter<__VA_ARGS__>())

#endif //TYPE_LIST_FILTER_H
