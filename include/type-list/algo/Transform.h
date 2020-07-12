//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_TRANSFORM_H
#define TYPE_LIST_TRANSFORM_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/FiniteListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/base/TypeList.h>
#include <type-list/base/Value.h>
#include <type-list/base/ListWrapper.h>

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

template<template <auto> typename F>
struct MapperAdapter {
    template<typename T>
    struct Mapper {
        using type = Value<F<T::value>::value>;
    };
};
template<FiniteValueListConcept IN, template <auto> typename F>
struct ValueTransform {
    using type = typename detail::Transform
            < List<IN>
            , MapperAdapter<F>::template Mapper
            >::type;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_TRANSFORM_H
