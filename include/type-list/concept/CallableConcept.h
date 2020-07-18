//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_CALLABLECONCEPT_H
#define TYPE_LIST_CALLABLECONCEPT_H

#include <type-list/type-list-ns.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<template <typename ...> typename F>
    struct __secrete_contains_template {};
}

template<typename T>
concept CallableConcept = requires {
    typename detail::__secrete_contains_template<T::template apply>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_CALLABLECONCEPT_H
