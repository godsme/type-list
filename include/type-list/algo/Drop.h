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

TYPE_LIST_NS_END

#define __TL_drop(in, n) TYPE_LIST_NS::Drop_t<in, n>

#endif //TYPE_LIST_DROP_H
