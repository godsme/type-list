//
// Created by godsme on 7/16/20.
//

#ifndef TYPE_LIST_BIND_H
#define TYPE_LIST_BIND_H

#include <type-list/type-list-ns.h>
#include <type-list/types/List.h>
#include <type-list/algo/Drop.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<template<typename ...> typename C,
            typename ... ARGS>
    struct Partial {
        template<typename ... MORE>
        using apply = C<ARGS..., MORE...>;
    };

    struct PlaceHolderSignature {
    };

    template<typename T>
    concept IsPlaceHolder = std::is_base_of_v<PlaceHolderSignature, T>;

    template<typename T>
    concept IsNotPlaceHolder = !IsPlaceHolder<T>;

    template<template<typename ...> typename C, typename REST, typename ... ARGS>
    struct DoBind {
        using type = C<>;
    };

    template<template<typename ...> typename C, typename REST, IsPlaceHolder H, typename ... ARGS>
    struct DoBind<C, REST, H, ARGS...> {
        using T = typename __TL_Drop(REST, H::value - 1)::Head;
        using type = typename DoBind<Partial<C, T>::template apply, REST, ARGS...>::type;
    };

    template<template<typename ...> typename C, typename REST, IsNotPlaceHolder H, typename ... ARGS>
    struct DoBind<C, REST, H, ARGS...> {
        using type = typename DoBind<Partial<C, H>::template apply, REST, ARGS...>::type;
    };
}

template<template<typename ...> typename C, typename ... ARGS>
struct Bind {
    template<typename ... Ts>
    using apply = typename detail::DoBind<C, TypeList<Ts...>, ARGS...>::type;
};

namespace detail {
    template<size_t N>
    struct Parameter : PlaceHolderSignature {
        constexpr static size_t value = N;
    };
}

using _1_ = detail::Parameter<1>;
using _2_ = detail::Parameter<2>;
using _3_ = detail::Parameter<3>;
using _4_ = detail::Parameter<4>;
using _5_ = detail::Parameter<5>;
using _6_ = detail::Parameter<6>;
using _7_ = detail::Parameter<7>;
using _8_ = detail::Parameter<8>;
using _9_ = detail::Parameter<9>;

TYPE_LIST_NS_END

#define __TL_bind(...) TYPE_LIST_NS::Bind<__VA_ARGS__>::template apply

#endif //TYPE_LIST_BIND_H
