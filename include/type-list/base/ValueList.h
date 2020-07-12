//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUELIST_H
#define TYPE_LIST_VALUELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/base/Signatures.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct ValueListAllSignatures
        : ValueListSignature
        , ExportableListSignature
        , AppendableTypeList
{};

template<auto ... Vs>
struct ValueList : ValueListAllSignatures {
    constexpr static size_t size = sizeof...(Vs);
};

template<auto H, auto ... Vs>
struct ValueList<H, Vs...> : ValueListAllSignatures {
    constexpr static size_t size = sizeof...(Vs) + 1;
    constexpr static auto Head = H;
    using Tail = ValueList<Vs...>;
};

template<auto INIT, auto STEP = 1>
struct InfiniteIntList : ValueListSignature, InfiniteListSignature {
    constexpr static auto Head = INIT;
    using Tail = InfiniteIntList<INIT+STEP, STEP>;
};

template<auto V>
struct RepeatValueList : ValueListSignature, InfiniteListSignature {
    constexpr static auto Head = V;
    using Tail = RepeatValueList<V>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUELIST_H
