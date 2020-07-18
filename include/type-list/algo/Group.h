//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_GROUP_H
#define TYPE_LIST_GROUP_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/Value.h>
#include <type-list/algo/Curry.h>
#include <type-list/algo/Filter.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template <typename IN, template <typename, typename> typename EQ, typename ... OUT>
    struct Group;

    template <NonEmptyFiniteListConcept IN, template <typename, typename> typename EQ, typename ... OUT>
    class Group<IN, EQ, OUT...> {
        using part = __TL_Partition(__TL_curry(EQ, typename IN::Head), typename IN::Tail);
    public:
        using type = typename Group<List<typename part::rest>, EQ, OUT...,
        typename part::satisfied::template prependType<typename IN::Head>>::type;
    };

    template <EmptyFiniteListConcept IN, template <typename, typename> typename EQ, typename ... OUT>
    struct Group<IN, EQ, OUT...> {
        using type = TypeList<OUT...>;
    };
}

namespace detail {
    __TL_lambda(GroupType, typename EQ, typename IN);

    __TL_lambda(GroupType, TypeTemplateConcept EQ, NonEmptyFiniteListConcept IN)
    <EQ, IN>
    __return_apply_t(detail::Group, List<IN>, EQ::template apply);

    __TL_lambda(GroupType, ValueConcept EQ, NonEmptyFiniteListConcept IN)
    <EQ, IN> {
        __TL_lambda(Eq, ValueConcept T1, ValueConcept T2)
        __return_v(EQ::value(T1::value, T2::value));
        __result_t(__TL_apply_t(detail::Group, List<IN>, Eq));
    };

    __TL_lambda(GroupType, ValueTemplateConcept EQ, NonEmptyFiniteListConcept IN)
    <EQ, IN> {
        __TL_lambda(Eq, ValueConcept T1, ValueConcept T2)
        __return_apply_v(EQ::template apply, T1::value, T2::value);
        __result_t(__TL_apply_t(detail::Group, List<IN>, Eq));
    };

    __TL_lambda(GroupType,
                typename EQ, EmptyListConcept IN)
    <EQ, IN> __return_t(EmptyList);
}

template<typename EQ, typename IN>
using Group_t = typename detail::GroupType<EQ, List<IN>>::type;

TYPE_LIST_NS_END

#define __TL_Group(eq, ...) TYPE_LIST_NS::Group_t<__TL_toType(eq), __VA_ARGS__>

#endif //TYPE_LIST_GROUP_H
