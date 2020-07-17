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
struct TypeTemplateSignature{};
template<template<typename> typename F>
struct TypeTemplate : TypeTemplateSignature {
    template<typename Ts>
    using apply = F<Ts>;
};

template<typename T>
concept TypeTemplateConcept = \
std::is_base_of_v<TypeTemplateSignature, T>;

/////////////////////////////////////////////////////////////////////////
struct ValueTemplateSignature{};
template<template<auto> typename F>
struct ValueTemplate : ValueTemplateSignature {
    template<auto Vs>
    using apply = F<Vs>;
};

template<typename T>
concept ValueTemplateConcept = \
std::is_base_of_v<ValueTemplateSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUE_H
