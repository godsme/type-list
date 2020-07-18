//
// Created by godsme on 7/15/20.
//

#ifndef TYPE_LIST_CURRY_H
#define TYPE_LIST_CURRY_H

#include <type-list/type-list-ns.h>
#include <type-list/types/TemplateDeduce.h>
#include <cstddef>
#include <type_traits>

TYPE_LIST_NS_BEGIN

struct TypeCallableSignature{};

namespace detail {
    template<template<typename ...> typename C, size_t N, typename ... Ts>
    struct CurryTrait : TypeCallableSignature {
        template<typename ...MORE>
        using apply = C<Ts..., MORE...>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 1, Ts...> : TypeCallableSignature {
        template<typename T1>
        using apply = C<Ts..., T1>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 2, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2>
        using apply = C<Ts..., T1, T2>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 3, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3>
        using apply = C<Ts..., T1, T2, T3>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 4, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4>
        using apply = C<Ts..., T1, T2, T3, T4>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 5, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4, typename T5>
        using apply = C<Ts..., T1, T2, T3, T4, T5>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 6, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        using apply = C<Ts..., T1, T2, T3, T4, T5, T6>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 7, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        using apply = C<Ts..., T1, T2, T3, T4, T5, T6, T7>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 8, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        using apply = C<Ts..., T1, T2, T3, T4, T5, T6, T7, T8>;
    };

    template<template<typename ...> typename C, typename ... Ts>
    struct CurryTrait<C, 9, Ts...> : TypeCallableSignature {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        using apply = C<Ts..., T1, T2, T3, T4, T5, T6, T7, T8, T9>;
    };

    template<template<typename ...> typename C, typename Type, typename ... Ts>
    struct DoCurry : TypeCallableSignature {
        template<typename ... MORE>
        using apply = C<Ts..., MORE...>;
    };

    template<template<typename ...> typename C, NumberObjConcept Type, typename ... Ts>
    struct DoCurry<C, Type, Ts...>
            : CurryTrait<C, Type::value - sizeof...(Ts), Ts...> {};
}

template<template<typename ...> typename C, typename ... Ts>
using Curry = detail::DoCurry<C, decltype(detail::SpecDeduceArgs<C>(detail::derived_sig{})), Ts...>;

TYPE_LIST_NS_END

#define __TL_curry(...) TYPE_LIST_NS::Curry<__VA_ARGS__>::template apply
#define __TL_curry_t(...) TYPE_LIST_NS::Curry<__VA_ARGS__>

#endif //TYPE_LIST_CURRY_H
