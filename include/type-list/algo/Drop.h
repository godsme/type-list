//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_DROP_H
#define TYPE_LIST_DROP_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Drop, ListConcept IN, size_t N);

    __TL_lambda(Drop, NonEmptyListConcept IN, size_t N)
    <IN, N> __return_apply_t(Drop
            , typename IN::Tail
            , N-1);

    __TL_lambda(Drop, ListConcept IN)
    <IN, 0> __return_apply_t(detail::EmptyListTrait, IN);
}

template<ListConcept IN, size_t N>
using Drop_t = __TL_apply_t(detail::Drop, IN, N);

__TL_lambda(Drop, size_t N)
__return_lambda_t(__TL_params(ListConcept IN), __TL_apply(Drop_t, IN, N));

TYPE_LIST_NS_END

#define __TL_Drop(...) TYPE_LIST_NS::Drop_t<__VA_ARGS__>
#define __TL_drop(...) TYPE_LIST_NS::Drop<__VA_ARGS__>

#endif //TYPE_LIST_DROP_H
