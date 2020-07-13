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
#include <type-list/base/ValueList.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template
      < FiniteListConcept            IN
      , template <typename> typename F
      , typename                     OUT>
    struct Transform {
        using type = OUT;
    };

    template
       < NonEmptyFiniteListConcept    IN
       , template <typename> typename F
       , typename                     OUT>
    struct Transform<IN, F, OUT> {
        using type = typename Transform
                < typename IN::Tail
                , F
                , typename OUT::template appendType<typename F<typename IN::Head>::type>
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

template<template <auto> typename F>
struct ValueToTypeMapperAdapter {
    template<typename T>
    struct Mapper {
        using type = typename F<T::value>::type;
    };
};

template<template <auto> typename F>
concept ValueToValueConcept = requires {
    F<0>::value;
};

template<template <auto> typename F>
concept ValueToTypeConcept = requires {
    typename F<0>::type;
};

namespace detail {
template<FiniteValueListConcept IN, template <auto> typename F>
struct ValueTransformer;

template<FiniteValueListConcept IN, template <auto> typename F>
requires ValueToValueConcept<F>
struct ValueTransformer<IN, F> {
    using type = typename detail::Transform
            < List<IN>
            , MapperAdapter<F>::template Mapper
            , ValueList<>
            >::type;
};

template<FiniteValueListConcept IN, template <auto> typename F>
requires ValueToTypeConcept<F>
struct ValueTransformer<IN, F> {
    using type = typename detail::Transform
            < List<IN>
            , ValueToTypeMapperAdapter<F>::template Mapper
            , TypeList<>
            >::type;
};
}

template<FiniteValueListConcept IN, template <auto> typename F>
using TransformValue_t  = typename detail::ValueTransformer<IN, F>::type;

template<FiniteTypeListConcept IN, template <typename > typename F>
using Transform_t  =
typename detail::Transform< IN, F, TypeList<>>::type;

TYPE_LIST_NS_END

#endif //TYPE_LIST_TRANSFORM_H
