//
// Created by godsme on 7/15/20.
//

#ifndef TYPE_LIST_CURRY_H
#define TYPE_LIST_CURRY_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

template<template<typename ...> typename C,
        typename ... ARGS>
struct Curry {
    template<typename ... MORE>
    using apply = Curry<C, ARGS..., MORE...>;
};

template<template<typename ...> typename C,
        typename ... ARGS> requires requires { typename C<ARGS...>; }
struct Curry<C, ARGS...> {
    using type = C<ARGS...>;
};

TYPE_LIST_NS_END

#define __TL_curry(...) TYPE_LIST_NS::Curry<__VA_ARGS__>::template apply

#endif //TYPE_LIST_CURRY_H
