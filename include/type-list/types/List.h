//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LIST_H
#define TYPE_LIST_LIST_H

#include <type-list/types/TypeList.h>
#include <type-list/types/ValueList.h>

TYPE_LIST_NS_BEGIN

struct EmptyList : ListSignature, AppendableSignature {
    template<ListConcept T>
    using appendList = T;

    template<ListConcept T>
    using prependList = T;
};

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
