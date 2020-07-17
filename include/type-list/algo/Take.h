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
#include <type-list/types/Lambda.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Take, ListConcept IN, size_t N, ListConcept OUT);

    __TL_lambda(Take, NonEmptyListConcept IN, size_t N, ListConcept OUT)
    <IN, N, OUT> __return_apply_t(Take
                    , typename IN::Tail
                    , N-1
                    , typename OUT::template appendType<typename IN::Head>);

    __TL_lambda(Take, ListConcept IN, ListConcept OUT)
    <IN, 0, OUT> __return_t(OUT);
}

namespace detail {
    __TL_lambda(TakeTrait, __Set(IN), size_t N);

//    __TL_lambda(TakeTrait, TypeListConcept IN, size_t N)
//    <IN, N> __return_apply_t(detail::Take, IN, N, TypeList<>);

    __TL_lambda(TakeTrait, ListConcept IN, size_t N)
    <IN, N> __return_apply_t(detail::Take, List<IN>, N, EmptyList);

    __TL_lambda(TakeTrait, EmptyListConcept IN)
    <IN, 0> __return_t(EmptyList);
}

template<typename N, ListConcept IN>
using Take_t = __TL_apply_t(detail::TakeTrait, IN, N::value);

//__TL_lambda(Take, size_t N)
//__return_lambda_t(__TL_params(ListConcept IN), __TL_apply(Take_t, N, IN));

TYPE_LIST_NS_END

#define __TL_Take(n, in) TYPE_LIST_NS::Take_t<TYPE_LIST_NS::Value<n>, in>


#endif //TYPE_LIST_TAKE_H
