//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_DROP_H
#define TYPE_LIST_DROP_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Drop, ListConcept IN, size_t N);

    template< NonEmptyListConcept IN, size_t N>
    struct Drop<IN, N>
        __return_apply_t(Drop
            , typename IN::Tail
            , N-1);

    template<ListConcept IN>
    struct Drop<IN, 0>
        __return_t(IN);
}

template<ListConcept IN, size_t N>
using Drop_t = __TL_apply_t(detail::Drop, IN, N);

TYPE_LIST_NS_END

#define __TL_drop(in, n) TYPE_LIST_NS::Drop_t<in, n>

#endif //TYPE_LIST_DROP_H
