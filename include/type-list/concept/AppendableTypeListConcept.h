//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_APPENDABLETYPELISTCONCEPT_H
#define TYPE_LIST_APPENDABLETYPELISTCONCEPT_H

#include <type-list/base/Signatures.h>
#include <type-list/concept/ListConcept.h>
#include <type_traits>

TYPE_LIST_NS_BEGIN

template<typename T>
concept AppendableTypeListConcept =
        ListConcept<T> &&
        std::is_base_of_v<AppendableTypeList, T>;


TYPE_LIST_NS_END

#endif //TYPE_LIST_APPENDABLETYPELISTCONCEPT_H
