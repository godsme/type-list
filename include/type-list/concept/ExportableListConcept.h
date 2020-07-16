//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_EXPORTABLELISTCONCEPT_H
#define TYPE_LIST_EXPORTABLELISTCONCEPT_H

#include <type-list/types/Signatures.h>
#include <type-list/concept/ListConcept.h>
#include <type-list/concept/TypeListConcept.h>
#include <type-list/concept/ValueListConcept.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept ExportableListConcept = ListConcept<T> &&
        std::is_base_of_v<detail::ExportableListSignature, T>;

template<typename T>
concept ExportableTypeListConcept = \
TypeListConcept<T> && ExportableListConcept<T>;

template<typename T>
concept ExportableValueListConcept = \
ValueListConcept<T> && ExportableListConcept<T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_EXPORTABLELISTCONCEPT_H
