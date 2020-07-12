//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_NONEMPTYLISTCONCEPT_H
#define TYPE_LIST_NONEMPTYLISTCONCEPT_H

#include <type-list/type-list-ns.h>
#include <concepts>
#include <type_traits>
#include <type-list/Signatures.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept NonEmptyListConcept =
        std::is_base_of_v<ListSignature, T> &&
        requires {
            typename T::Head;
            typename T::Tail;
        };

TYPE_LIST_NS_END

#endif //TYPE_LIST_NONEMPTYLISTCONCEPT_H
