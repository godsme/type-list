//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_PAIR_H
#define TYPE_LIST_PAIR_H

#include <type-list/types/Signatures.h>
#include <type-list/types/EmptyList.h>

TYPE_LIST_NS_BEGIN

template<typename T1, typename T2>
struct Pair {
    using first  = T1;
    using second = T2;
};

TYPE_LIST_NS_END

#define __TL_pair(...) TYPE_LIST_NS::Pair<__VA_ARGS__>

#endif //TYPE_LIST_PAIR_H
