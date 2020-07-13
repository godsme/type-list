//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LIST_H
#define TYPE_LIST_LIST_H

#include <type-list/base/TypeList.h>
#include <type-list/base/ValueList.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename ... Ts>
    auto DeduceListType() -> TypeList<Ts...>;

    template<auto ... Vs>
    auto DeduceListType() -> ValueList<Vs...>;
}

TYPE_LIST_NS_END

#define __TL_list(p, ...) \
decltype(TYPE_LIST_NS::detail::DeduceListType<p, __VA_ARGS__>())

#endif //TYPE_LIST_LIST_H
