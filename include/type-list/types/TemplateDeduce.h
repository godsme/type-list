//
// Created by godsme on 7/18/20.
//

#ifndef TYPE_LIST_TEMPLATEDEDUCE_H
#define TYPE_LIST_TEMPLATEDEDUCE_H

#include <type-list/type-list-ns.h>
#include <cstddef>
#include <type_traits>

TYPE_LIST_NS_BEGIN

namespace detail {
    struct base_sig {
    };
    struct derived_sig : base_sig {
    };
    struct not_me {
    };
    struct number_signature {
    };

    template<size_t V>
    struct ParameterNumber : number_signature {
        constexpr static auto value = V;
    };

    template<typename T>
    concept NumberObjConcept = std::is_base_of_v<number_signature, T>;

    template<template<typename> typename>
    auto DeduceArgs() -> ParameterNumber<1>;

    template<template<typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<2>;

    template<template<typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<3>;

    template<template<typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<4>;

    template<template<typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<5>;

    template<template<typename, typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<6>;

    template<template<typename, typename, typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<7>;

    template<template<typename, typename, typename, typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<8>;

    template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<9>;

    template<template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> typename>
    auto DeduceArgs() -> ParameterNumber<10>;

    template<template<typename...> typename F>
    auto SpecDeduceArgs(base_sig) -> ParameterNumber<1000000000>; // a meaningless big number

    template<template<typename...> typename F>
    auto SpecDeduceArgs(derived_sig) -> decltype(DeduceArgs<F>());
}

#define __DEDUCE_TEMPLATE_ARGS(c) decltype(detail::SpecDeduceArgs<c>(detail::derived_sig{}))

TYPE_LIST_NS_END

#endif //TYPE_LIST_TEMPLATEDEDUCE_H
