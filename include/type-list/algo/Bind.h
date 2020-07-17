//
// Created by godsme on 7/16/20.
//

#ifndef TYPE_LIST_BIND_H
#define TYPE_LIST_BIND_H

#include <type-list/type-list-ns.h>
#include <type-list/types/List.h>
#include <type-list/algo/Drop.h>
#include <type-list/algo/Curry.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

//template<template<typename ...> typename C, typename FAKE, typename ACTUAL, typename = void>
//struct Combine {
//    template<typename ... Ts>
//    using type = C<Ts...>;
//};
//
//template<template<typename ...> typename C, typename FAKE, typename ACTUAL>
//class Combine<C, FAKE, ACTUAL,
//        std::enable_if_t<std::is_void_v<typename ACTUAL::Head>>> {
//    template <typename ... Ts>
//    using Next = C<typename FAKE::Head, Ts...>;
//
//public:
//    template<typename ... Ts>
//    using type = typename Combine<Next, typename FAKE::Tail, typename ACTUAL::Tail>::template type<Ts...>;
//};
//
//template<template<typename ...> typename C, typename FAKE, typename ACTUAL>
//class Combine<C, FAKE, ACTUAL,
//        std::enable_if_t<!std::is_void_v<typename ACTUAL::Head>>> {
//    template <typename ... Ts>
//    using Next = C<typename ACTUAL::Head, Ts...>;
//public:
//    template<typename ... Ts>
//    using type = typename Combine<Next, FAKE, typename ACTUAL::Tail>::template type<Ts...>;
//};
//
//namespace detail {
//    template<template<typename ...> typename C, size_t N, typename ARGS>
//    struct DoBind;
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 0, ARGS> {
//        template<typename ... Ts>
//        using apply = C<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 1, ARGS> {
//        template<typename T0, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 2, ARGS> {
//        template<typename T0, typename T1, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 3, ARGS> {
//        template<typename T0, typename T1, typename T2, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 4, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 5, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename T5, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4, T5>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 6, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename T5, typename T6, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4, T5, T6>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 7, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename T5, typename T6, typename T7, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4, T5, T6, T7>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 8, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename T5, typename T6, typename T7, typename T8, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4, T5, T6, T7, T8>, ARGS>::template type<Ts...>;
//    };
//
//    template<template<typename ...> typename C, typename ARGS>
//    struct DoBind<C, 9, ARGS> {
//        template<typename T0, typename T1, typename T2, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename ... Ts>
//        using apply = typename Combine<C, TypeList<T0, T1, T2, T4, T5, T6, T7, T8, T9>, ARGS>::template type<Ts...>;
//    };
//}
//
//
//namespace detail {
//    template<size_t I, typename T, typename ALL_ARGS>
//    struct ComposeArgs {
//        using args = typename ComposeArgs<I-1, T, typename ALL_ARGS::template appendType<void>>::args;
//    };
//
//    template<typename T, typename ALL_ARGS>
//    struct ComposeArgs<0, T, ALL_ARGS> {
//        using args = typename ALL_ARGS::template appendType<T>;
//    };
//}
//
//namespace detail {
//    template<typename ALL_ARGS, size_t LAST_INDEX,
//            size_t N, typename ... ARGS>
//    struct CalcArgs {
//        constexpr static size_t actualNum = N;
//        using args = ALL_ARGS;
//    };
//
//    template<typename ALL_ARGS, size_t LAST_INDEX,
//            size_t N, typename INDEX, typename T, typename ... ARGS>
//    class CalcArgs<ALL_ARGS, LAST_INDEX, N, INDEX, T, ARGS...> {
//        using argsSoFar = typename ComposeArgs<INDEX::value - LAST_INDEX, T, ALL_ARGS>::args;
//        using result = CalcArgs<argsSoFar, INDEX::value + 1, N + 1, ARGS...>;
//    public:
//        constexpr static size_t actualNum = result::actualNum;
//        using args = typename result::args;
//    };
//
//    template<typename ALL_ARGS, size_t LAST_INDEX,
//            size_t N, typename ILL_FORM, typename ... ARGS>
//    struct CalcArgs<ALL_ARGS, LAST_INDEX, N, ILL_FORM, ARGS...>;
//}

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
