//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_NONEMPTYLISTCONCEPT_H
#define TYPE_LIST_NONEMPTYLISTCONCEPT_H

#include <type-list/type-list-ns.h>
#include <concepts>
#include <type-list/types/Signatures.h>
#include <type-list/concept/ListConcept.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/TypeListConcept.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept IsNonEmptyTypeList =
requires {
    typename T::Head;
    typename T::Tail;
};

template<typename T>
concept IsNonEmptyValueList = requires {
    T::Head;
    typename T::Tail;
};

template<typename T>
concept EmptyListConcept =
ListConcept<T> && !IsNonEmptyValueList<T> && !IsNonEmptyTypeList<T>;

template<typename T>
concept NonEmptyListConcept =
ListConcept<T> && (IsNonEmptyValueList<T> || IsNonEmptyTypeList<T>);

template<typename T>
concept NonEmptyTypeListConcept =
TypeListConcept<T> && IsNonEmptyTypeList<T>;

template<typename T>
concept EmptyTypeListConcept =
ValueListConcept<T> && !IsNonEmptyTypeList<T>;

template<typename T>
concept EmptyValueListConcept =
ValueListConcept<T> && !IsNonEmptyValueList<T>;

template<typename T>
concept InfiniteConcept = std::is_base_of_v<InfiniteSignature, T>;

template<typename T>
concept InfiniteListConcept =
ListConcept<T> && InfiniteConcept<T>;

template<typename T>
concept InfiniteValueListConcept =
ValueListConcept<T> && InfiniteConcept<T>;

template<typename T>
concept FiniteValueListConcept =
ValueListConcept<T> && !InfiniteConcept<T>;

template<typename T>
concept NonEmptyFiniteValueListConcept = \
FiniteValueListConcept<T> && IsNonEmptyValueList<T>;

template<typename T>
concept NonEmptyValueListConcept = \
ValueListConcept<T> && IsNonEmptyValueList<T>;

template<typename T>
concept EmptyFiniteValueListConcept = \
FiniteValueListConcept<T> && !IsNonEmptyValueList<T>;

template<typename T>
concept FiniteListConcept =
ListConcept<T> && !InfiniteConcept<T>;


template<typename T>
concept FiniteTypeListConcept =
TypeListConcept<T> && !InfiniteConcept<T>;

template<typename T>
concept NonEmptyFiniteListConcept =
NonEmptyListConcept<T> && FiniteListConcept<T>;

template<typename T>
concept NonEmptyFiniteTypeListConcept =
NonEmptyTypeListConcept<T> && FiniteListConcept<T>;

template<typename T>
concept EmptyFiniteListConcept =
!InfiniteConcept<T> && !NonEmptyListConcept<T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_NONEMPTYLISTCONCEPT_H
