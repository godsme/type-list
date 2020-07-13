//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_APPENDABLETYPELISTCONCEPT_H
#define TYPE_LIST_APPENDABLETYPELISTCONCEPT_H

#include <type-list/types/Signatures.h>
#include <type-list/concept/ListConcept.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

template<typename T>
concept AppendableListConcept =
        ListConcept<T> &&
        std::is_base_of_v<AppendableSignature, T>;


TYPE_LIST_NS_END

#endif //TYPE_LIST_APPENDABLETYPELISTCONCEPT_H
