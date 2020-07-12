//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUELIST_H
#define TYPE_LIST_VALUELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/base/Signatures.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

template<auto INIT, auto STEP = 1>
struct InfiniteIntList : ValueListSignature {
    constexpr static auto Head = INIT;
    using Tail = InfiniteIntList<INIT+STEP, STEP>;
};

template<auto V>
struct RepeatValueList : ValueListSignature {
    constexpr static auto Head = V;
    using Tail = RepeatValueList<V>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUELIST_H
