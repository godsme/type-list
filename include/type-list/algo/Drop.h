//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_DROP_H
#define TYPE_LIST_DROP_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    template
        < ListConcept IN
        , size_t      N>
    struct Drop;

    template
        < NonEmptyListConcept    IN
        , size_t                 N>
    struct Drop<IN, N> {
        using type = typename Drop
                < typename IN::Tail
                , N-1
                >::type;
    };

    template<NonEmptyListConcept IN>
    struct Drop<IN, 0> {
        using type = IN;
    };

    template<EmptyListConcept IN>
    struct Drop<IN, 0> {
        using type = IN;
    };
}

template<ListConcept IN, size_t N>
using Drop_t = typename detail::Drop<IN, N>::type;

TYPE_LIST_NS_END

#endif //TYPE_LIST_DROP_H
