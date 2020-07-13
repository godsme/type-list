//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUE_H
#define TYPE_LIST_VALUE_H

#include <type-list/type-list-ns.h>

TYPE_LIST_NS_BEGIN

struct ValueSignature{};

template<auto V>
struct Value : ValueSignature {
    constexpr static auto value = V;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUE_H
