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
    __TL_lambda(Drop, size_t N, ListConcept IN);

    __TL_lambda(Drop, size_t N, NonEmptyListConcept IN)
    <N, IN> __return_apply_t(Drop
            , N-1
            , typename IN::Tail);

    __TL_lambda(Drop, ListConcept IN)
    <0, IN> __return_apply_t(detail::EmptyListTrait, IN);
}

template<typename N, ListConcept IN>
using Drop_t = __TL_apply_t(detail::Drop, N::value, IN);

TYPE_LIST_NS_END

#define __TL_Drop(n, ...) TYPE_LIST_NS::Drop_t<TYPE_LIST_NS::Value<n>, __VA_ARGS__>

#endif //TYPE_LIST_DROP_H
