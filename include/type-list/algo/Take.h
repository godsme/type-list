//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_TAKE_H
#define TYPE_LIST_TAKE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/List.h>
#include <type-list/types/ListWrapper.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    template
       < ListConcept IN
       , size_t      N
       , ListConcept OUT>
    struct Take;

    template
       < NonEmptyListConcept    IN
       , size_t                 N
       , ListConcept            OUT>
    struct Take<IN, N, OUT> {
        using type = typename Take
                < typename IN::Tail
                , N-1
                , typename OUT::template appendType<typename IN::Head>
                >::type;
    };

    template<ListConcept IN, ListConcept OUT>
    struct Take<IN, 0, OUT> {
        using type = OUT;
    };
}

namespace detail {
    template<typename IN, size_t N>
    class TakeTrait;


    template<ValueListConcept IN, size_t N>
    struct TakeTrait<IN, N> {
        using type = typename detail::Take<List<IN>, N, ValueList<>>::type;
    };

    template<TypeListConcept IN, size_t N>
    struct TakeTrait<IN, N> {
        using type = typename detail::Take<IN, N, TypeList<>>::type;
    };

    template<typename IN> requires std::is_same_v<EmptyList, IN>
    struct TakeTrait<IN, 0> {
        using type = EmptyList;
    };
}
template<ListConcept IN, size_t N>
using Take_t = typename detail::TakeTrait<IN, N>::type;

TYPE_LIST_NS_END

#define __TL_take(in, n) TYPE_LIST_NS::Take_t<in, n>

#endif //TYPE_LIST_TAKE_H
