//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODETRAITS_H
#define TYPE_LIST_NODETRAITS_H

#include <type-list/algo/Unique.h>
#include <type-list/types/List.h>

template<typename NODE>
struct NodeTrait {
    using NodeList = __TL_list(NODE);
};

template<typename PRED, typename NODE>
struct Maybe {
    using PredType = PRED;
    using NodeList = __TL_unique(typename NodeTrait<NODE>::NodeList);
};

template<typename COND, typename NODE>
struct NodeTrait<Maybe<COND, NODE>> {
    using NodeList = typename Maybe<COND, NODE>::NodeList;
};

template<typename PRED, typename NODE_1, typename NODE_2>
struct Exclusive {
    using PredType = PRED;
    using NodeList = __TL_unique(
            typename NodeTrait<NODE_1>::NodeList::template appendList<typename NodeTrait<NODE_2>::NodeList>);
};

template<typename COND, typename NODE_1, typename NODE_2>
struct NodeTrait<Exclusive<COND, NODE_1, NODE_2>> {
    using NodeList = typename Exclusive<COND, NODE_1, NODE_2>::NodeList;
};

#define __maybe(...) Maybe<__VA_ARGS__>
#define __exclusive(...) Exclusive<__VA_ARGS__>

#endif //TYPE_LIST_NODETRAITS_H
