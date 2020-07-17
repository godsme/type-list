//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_GROUP_H
#define TYPE_LIST_GROUP_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/ListWrapper.h>
#include <type-list/types/Value.h>
#include <type-list/algo/Curry.h>
#include <type-list/algo/Filter.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template <typename IN, template <typename, typename> typename EQ, typename ... OUT>
    struct Group;

    template <NonEmptyFiniteListConcept IN, template <typename, typename> typename EQ, typename ... OUT>
    class Group<IN, EQ, OUT...> {
        using part = __TL_Partition(IN::TAIL, __TL_curry(EQ, typename IN::Head));
    public:
        using type = typename Group<typename part::rest, EQ, OUT..., typename part::satisfied::template prependType<IN::Head>>::type;
    };

    template <EmptyFiniteListConcept IN, template <typename, typename> typename EQ, typename ... OUT>
    struct Group<IN, EQ, OUT...> {
        using type = TypeList<OUT...>;
    };
}

namespace detail {

}

TYPE_LIST_NS_END

#endif //TYPE_LIST_GROUP_H
