//
// Created by godsme on 7/15/20.
//

#ifndef TYPE_LIST_CURRY_H
#define TYPE_LIST_CURRY_H

#include <type-list/type-list-ns.h>

TYPE_LIST_NS_BEGIN

template<template<typename ...> typename C,
        typename ... ARGS>
struct Curry {
    template<typename ... MORE>
    using apply = C<ARGS..., MORE...>;
};

template<template<typename ...> typename C,
        typename ... ARGS>
struct Curry1 {
    template<typename T>
    using apply = C<ARGS..., T>;
};

TYPE_LIST_NS_END

#define __TL_curry(...) TYPE_LIST_NS::Curry<__VA_ARGS__>::template apply
#define __TL_curry_t(...) TYPE_LIST_NS::Curry1<__VA_ARGS__>

#endif //TYPE_LIST_CURRY_H
