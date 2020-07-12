//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_2_TYPELIST_H
#define TYPE_LIST_2_TYPELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/Signatures.h>

TYPE_LIST_NS_BEGIN

template <typename ... Ts>
struct TypeList : ExportableTypeListSignature {
    constexpr static size_t size = sizeof...(Ts); // actually 0

    template <template <typename ...> typename RESULT>
    using exportTo = RESULT<Ts...>;
};

template <typename H, typename ... Ts>
struct TypeList<H, Ts...> : ExportableTypeListSignature {
    constexpr static size_t size = sizeof...(Ts) + 1;
    using Head = H;
    using Tail = TypeList<Ts...>;

    template <template <typename ...> typename RESULT>
    using exportTo = RESULT<H, Ts...>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_2_TYPELIST_H
