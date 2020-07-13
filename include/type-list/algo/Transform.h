//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_TRANSFORM_H
#define TYPE_LIST_TRANSFORM_H

#include <type-list/type-list-ns.h>
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

namespace detail {
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

    template<template <auto> typename F, auto V>
    concept ValueToValueConcept = requires {
        F<V>::value;
    };

    template<template <auto> typename F, auto V>
    concept ValueToTypeConcept = requires {
        typename F<V>::type;
    };

    template<FiniteValueListConcept IN, template <auto> typename F>
    struct ValueTransformer;

    template<NonEmptyFiniteValueListConcept IN, template <auto> typename F>
    requires ValueToValueConcept<F, IN::Head>
    struct ValueTransformer<IN, F> {
        using type = typename detail::Transform
                < List<IN>
                , MapperAdapter<F>::template Mapper
                , ValueList<>
                >::type;
    };

    template<EmptyFiniteValueListConcept IN, template <auto> typename F>
    requires ValueToValueConcept<F, 0>
    struct ValueTransformer<IN, F> {
        using type = ValueList<>;
    };

    template<NonEmptyFiniteValueListConcept IN, template <auto> typename F>
    requires ValueToTypeConcept<F, IN::Head>
    struct ValueTransformer<IN, F> {
        using type = typename detail::Transform
                < List<IN>
                , ValueToTypeMapperAdapter<F>::template Mapper
                , TypeList<>
                >::type;
    };

    template<EmptyFiniteValueListConcept IN, template <auto> typename F>
    requires ValueToTypeConcept<F, 0>
    struct ValueTransformer<IN, F> {
        using type = TypeList<>;
    };
}

template<FiniteValueListConcept IN, template <auto> typename F>
using TransformValue_t = typename detail::ValueTransformer<IN, F>::type;

namespace detail {
    template<auto F>
    struct Value2ValueMapperAdapter {
        template<typename T>
        struct Mapper {
            using type = Value<F(T::value)>;
        };
    };

    template<FiniteValueListConcept IN, auto F>
    struct Value2ValueTransformer {
        using type = typename detail::Transform
                < List<IN>
                , Value2ValueMapperAdapter<F>::template Mapper
                , ValueList<>
                >::type;
    };
}

template<FiniteValueListConcept IN, auto F>
using TransformValueF_t = typename detail::Value2ValueTransformer<IN, F>::type;

namespace detail {
    template<template <typename> typename F>
    struct Type2ValueMapperAdapter {
        template<typename T>
        struct Mapper {
            using type = Value<F<T>::value>;
        };
    };

    template<template <typename T> typename F>
    concept TypeToValueConcept = requires {
        F<int>::value;
    };

    template<template <typename T> typename F>
    concept TypeToTypeConcept = requires {
        typename F<int>::type;
    };

    template<FiniteTypeListConcept IN, template <typename> typename F>
    struct TypeTransformer;

    template<FiniteTypeListConcept IN, template <typename> typename F>
    requires TypeToValueConcept<F>
    struct TypeTransformer<IN, F> {
        using type = typename detail::Transform
                < IN
                , Type2ValueMapperAdapter<F>::template Mapper
                , ValueList<>
                >::type;
    };

    template<FiniteTypeListConcept IN, template <typename> typename F>
    requires TypeToTypeConcept<F>
    struct TypeTransformer<IN, F> {
        using type = typename detail::Transform
                < IN
                , F
                , TypeList<>
                >::type;
    };
}

template<FiniteTypeListConcept IN, template <typename > typename F>
using Transform_t = typename detail::TypeTransformer< IN, F>::type;

namespace detail {
    template<FiniteListConcept IN, template <typename > typename F>
    auto DeductTransform() -> Transform_t<IN, F>;

    template<FiniteListConcept IN, template <auto > typename F>
    auto DeductTransform() -> TransformValue_t<IN, F>;

    template<FiniteListConcept IN, auto F>
    auto DeductTransform() -> TransformValueF_t<IN, F>;
}

TYPE_LIST_NS_END

#define __TL_map(IN, F) \
decltype(TYPE_LIST_NS::detail::DeductTransform<IN, F>())

#endif //TYPE_LIST_TRANSFORM_H
