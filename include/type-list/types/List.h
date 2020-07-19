//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LIST_H
#define TYPE_LIST_LIST_H

#include <type-list/types/Signatures.h>
#include <type-list/types/EmptyList.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<ValueListConcept LIST>
    struct __ValueListWrapper {
        using type = EmptyList;

        template<template<typename ...> typename RESULT>
        auto exportTo() -> RESULT<>;

        template<template<auto ...> typename RESULT>
        auto exportTo() -> RESULT<>;
    };

    template<NonEmptyValueListConcept LIST>
    struct __ValueListWrapper<LIST> {
        struct type : ListSignature, TypeListSignature {
            constexpr static size_t size = LIST::size;

            using Head = Value<LIST::Head>;
            using Tail = typename __ValueListWrapper<typename LIST::Tail>::type;

            template<template<auto ...> typename RESULT>
            auto exportTo() -> decltype(LIST::template exportTo<RESULT>());
        };
    };

    template<InfiniteValueListConcept T>
    struct InfiniteValueListWrapper
            : ListSignature
            , TypeListSignature
            , InfiniteSignature {
        using Head = Value<T::Head>;
        using Tail = InfiniteValueListWrapper<typename T::Tail>;
    };

    template<typename LIST>
    struct ListWrapperTrait {
        using type = LIST;
    };

    template<ValueListConcept T>
    struct ListWrapperTrait<T> {
        using type = typename __ValueListWrapper<T>::type;
    };

    template<InfiniteValueListConcept T>
    struct ListWrapperTrait<T> {
        using type = InfiniteValueListWrapper<T>;
    };
}

template <ListConcept LIST>
using List = typename detail::ListWrapperTrait<LIST>::type;

namespace detail {

    template<int, typename T, typename ... Ts>
    auto DeduceListType() -> TypeList<T, Ts...>;

    template <int>
    auto DeduceListType() -> EmptyList;

    template<int, auto V, auto ... Vs>
    auto DeduceListType() -> ValueList<V, Vs...>;

    template<typename T>
    auto DeduceRepeatListType() -> RepeatTypeList<T>;

    template<auto V>
    auto DeduceRepeatListType() -> RepeatValueList<V>;

    template<auto V, size_t TIMES>
    auto DeduceRepeatListType() -> LimitedRepeatValueList<V, TIMES>;

    template<typename T, size_t TIMES>
    auto DeduceRepeatListType() -> LimitedRepeatTypeList<T, TIMES>;
}

TYPE_LIST_NS_END

#define __TL_list(...) \
decltype(TYPE_LIST_NS::detail::DeduceListType<0, ##__VA_ARGS__>())

#define __TL_repeat(p, ...) \
decltype(TYPE_LIST_NS::detail::DeduceRepeatListType<p, ##__VA_ARGS__>())

#define __TL_infinite(...) TYPE_LIST_NS::InfiniteIntList<__VA_ARGS__>

#endif //TYPE_LIST_LIST_H
