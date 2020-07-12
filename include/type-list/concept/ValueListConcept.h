//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUELISTCONCEPT_H
#define TYPE_LIST_VALUELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

template<typename T>
concept ValueListConcept = std::is_base_of_v<ValueListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUELISTCONCEPT_H
