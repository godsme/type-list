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
#include <type-list/types/Value.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Partition,
                FiniteListConcept IN,
                __TL_lambda(PRED, typename),
                ListConcept SATISFIED = EmptyList,
                ListConcept REST = EmptyList,
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
    template<typename PRED, typename IN>
    struct PartitionType;

    template<TypeTemplateConcept PRED, NonEmptyFiniteTypeListConcept IN>
    struct PartitionType<PRED, IN> {
        using type = __TL_apply_t(detail::Partition,
                IN,
                PRED::template apply);
    };

    template<ValueConcept PRED, NonEmptyFiniteValueListConcept IN>
    struct PartitionType<PRED, IN> {
        __TL_lambda(Pred, typename T) __return_v(PRED::value(T::value));
        using type = __TL_apply_t(detail::Partition,
                     List<IN>,
                     Pred);
    };

    template<ValueTemplateConcept PRED, NonEmptyFiniteValueListConcept IN>
    struct PartitionType<PRED, IN> {
        __TL_lambda(Pred, typename T) __return_apply_v(PRED::template apply, T::value);
        using type = __TL_apply_t(detail::Partition,
                         List<IN>,
                         Pred);
    };

    template<typename PRED, EmptyListConcept IN>
    struct PartitionType<PRED, IN> {
        using type = struct {
            using satisfied = EmptyList;
            using rest      = EmptyList;
        };
    };
}

template<typename PRED, typename IN>
using Partition_t = typename detail::PartitionType<PRED, IN>::type;

template<typename PRED, typename IN>
using Filter_t = typename detail::PartitionType<PRED, IN>::type::satisfied;

TYPE_LIST_NS_END

#define __TL_Partition(pred, ...) TYPE_LIST_NS::Partition_t<__TL_toType(pred), __VA_ARGS__>
#define __TL_Filter(...) typename __TL_Partition(__VA_ARGS__)::satisfied

#endif //TYPE_LIST_FILTER_H
