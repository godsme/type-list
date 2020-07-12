//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_TRANSFORM_H
#define TYPE_LIST_TRANSFORM_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/FiniteListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/base/TypeList.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template
      < FiniteListConcept            IN
      , template <typename> typename F
      , typename                 ... OUT>
    struct Transform {
        using type = TypeList<OUT...>;
    };

    template
       < NonEmptyFiniteListConcept    IN
       , template <typename> typename F
       , typename                 ... OUT>
    struct Transform<IN, F, OUT...> {
        using type = typename Transform
                < typename IN::Tail
                , F
                , OUT... , F<typename IN::Head>
                >::type;
    };
}

    template<typename IN, template <auto> typename F>

TYPE_LIST_NS_END

#endif //TYPE_LIST_TRANSFORM_H
