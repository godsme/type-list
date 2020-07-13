//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_LISTCONCEPT_H
#define TYPE_LIST_LISTCONCEPT_H

#include <type-list/types/Signatures.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

template<typename T>
concept ListConcept = std::is_base_of_v<ListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_LISTCONCEPT_H
