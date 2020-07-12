//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_2_TYPELIST_H
#define TYPE_LIST_2_TYPELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/Signatures.h>

TYPE_LIST_NS_BEGIN

template <typename ... Ts>
struct TypeList : TypeListSignature {
    constexpr static size_t size = sizeof...(Ts); // actually 0
};

template <typename H, typename ... Ts>
struct TypeList<H, Ts...> : TypeListSignature {
    constexpr static size_t size = sizeof...(Ts) + 1;
    using Head = H;
    using Tail = TypeList<Ts...>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_2_TYPELIST_H
