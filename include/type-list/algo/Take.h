//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_TAKE_H
#define TYPE_LIST_TAKE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/List.h>
#include <cstddef>
#include <type-list/types/Lambda.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Take, size_t N, ListConcept IN, ListConcept OUT = EmptyList);

    __TL_lambda(Take, size_t N, NonEmptyListConcept IN, ListConcept OUT)
    <N, IN, OUT> __return_apply_t(Take
                    , N-1
                    , typename IN::Tail
                    , typename OUT::template appendType<typename IN::Head>);

    __TL_lambda(Take, ListConcept IN, ListConcept OUT)
    <0, IN, OUT> __return_t(OUT);
}

namespace detail {
    __TL_lambda(TakeTrait, size_t N, __Set(IN));

    __TL_lambda(TakeTrait, size_t N, ListConcept IN)
    <N, IN> __return_apply_t(detail::Take, N, IN);

    __TL_lambda(TakeTrait, EmptyListConcept IN)
    <0, IN> __return_t(EmptyList);
}

template<typename N, ListConcept IN>
using Take_t = __TL_apply_t(detail::TakeTrait, N::value, List<IN>);

//__TL_lambda(Take, size_t N)
//__return_lambda_t(__TL_params(ListConcept IN), __TL_apply(Take_t, N, IN));

TYPE_LIST_NS_END

#define __TL_Take(n, in) TYPE_LIST_NS::Take_t<TYPE_LIST_NS::Value<n>, in>


#endif //TYPE_LIST_TAKE_H
