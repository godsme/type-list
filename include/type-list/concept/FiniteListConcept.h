//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_FINITELISTCONCEPT_H
#define TYPE_LIST_FINITELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type-list/concept/ListConcept.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept FiniteListConcept =
    ListConcept<T> &&
    !std::is_base_of_v<InfiniteListSignature, T>;

template<typename T>
concept FiniteValueListConcept =
    ValueListConcept<T> &&
    !std::is_base_of_v<InfiniteListSignature, T>;

template<typename T>
concept NonEmptyFiniteListConcept =
        FiniteListConcept<T> && NonEmptyListConcept<T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_FINITELISTCONCEPT_H
