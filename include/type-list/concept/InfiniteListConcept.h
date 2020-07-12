//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_INFINITELISTCONCEPT_H
#define TYPE_LIST_INFINITELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type-list/concept/ListConcept.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept InfiniteListConcept =
        ListConcept<T> &&
        std::is_base_of_v<InfiniteListSignature, T>;

template<typename T>
concept InfiniteValueListConcept =
    ValueListConcept<T> &&
    std::is_base_of_v<InfiniteListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_INFINITELISTCONCEPT_H
