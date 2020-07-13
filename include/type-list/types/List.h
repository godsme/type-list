//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LIST_H
#define TYPE_LIST_LIST_H

#include <type-list/types/TypeList.h>
#include <type-list/types/ValueList.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename ... Ts>
    auto DeduceListType() -> TypeList<Ts...>;

    template<auto ... Vs>
    auto DeduceListType() -> ValueList<Vs...>;

    template<typename T>
    auto DeduceRepeatListType() -> RepeatTypeList<T>;

    template<auto V>
    auto DeduceRepeatListType() -> RepeatValueList<V>;
}

TYPE_LIST_NS_END

#define __TL_list(p, ...) \
decltype(TYPE_LIST_NS::detail::DeduceListType<p, __VA_ARGS__>())

#define __TL_repeat(p) \
decltype(TYPE_LIST_NS::detail::DeduceRepeatListType<p>())

#endif //TYPE_LIST_LIST_H
