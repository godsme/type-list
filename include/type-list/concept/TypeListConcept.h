//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_TYPELISTCONCEPT_H
#define TYPE_LIST_TYPELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

template<typename T>
concept TypeListConcept = std::is_base_of_v<TypeListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_TYPELISTCONCEPT_H
