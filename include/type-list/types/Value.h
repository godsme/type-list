//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUE_H
#define TYPE_LIST_VALUE_H

#include <type-list/type-list-ns.h>

TYPE_LIST_NS_BEGIN

/////////////////////////////////////////////////////////////////////////
struct ValueSignature{};
template<auto V>
struct Value : ValueSignature {
    constexpr static auto value = V;
};

template<typename T>
concept ValueConcept = std::is_base_of_v<ValueSignature, T>;

/////////////////////////////////////////////////////////////////////////
struct TypeCallableSignature{};
template<template<typename ...> typename F>
struct CallableT : TypeCallableSignature {
    template<typename ... Ts>
    using apply = F<Ts...>;
};

template<typename T>
concept TypeTemplateConcept = \
std::is_base_of_v<TypeCallableSignature, T>;

/////////////////////////////////////////////////////////////////////////
struct ValueCallableSignature{};
template<template<auto ...> typename F>
struct CallableV : ValueCallableSignature {
    template<auto ... Vs>
    using apply = F<Vs...>;
};

template<typename T>
concept ValueTemplateConcept = \
std::is_base_of_v<ValueCallableSignature, T>;

/////////////////////////////////////////////////////////
template<typename T>
auto DeduceType() -> T;

template<template<typename ...> typename F>
auto DeduceType() -> CallableT<F>;

template<template<auto ...> typename F>
auto DeduceType() -> CallableV<F>;

template<auto V>
auto DeduceType() -> Value<V>;

TYPE_LIST_NS_END

#define __TL_toType(...) decltype(TYPE_LIST_NS::DeduceType<__VA_ARGS__>())

#endif //TYPE_LIST_VALUE_H
