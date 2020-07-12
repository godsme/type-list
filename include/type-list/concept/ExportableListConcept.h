//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_EXPORTABLELISTCONCEPT_H
#define TYPE_LIST_EXPORTABLELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type-list/concept/ListConcept.h>

TYPE_LIST_NS_BEGIN

template<typename T>
concept ExportableListConcept = ListConcept<T> &&
        std::is_base_of_v<ExportableListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_EXPORTABLELISTCONCEPT_H
