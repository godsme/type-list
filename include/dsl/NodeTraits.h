//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODETRAITS_H
#define TYPE_LIST_NODETRAITS_H

#include <type-list/algo/Unique.h>

template<typename NODE>
struct NodeTrait {
    using NodeList = TYPE_LIST_NS::TypeList<NODE>;
};

template<typename PRED, typename NODE>
struct Maybe {
    using PredType = PRED;
    using NodeList = TYPE_LIST_NS::Unique_tl<typename NodeTrait<NODE>::NodeList>;
};

template<typename COND, typename NODE>
struct NodeTrait<Maybe<COND, NODE>> {
    using NodeList = typename Maybe<COND, NODE>::NodeList;
};

template<typename PRED, typename NODE_1, typename NODE_2>
struct Exclusive {
    using PredType = PRED;
    using NodeList = TYPE_LIST_NS::Unique_tl<
            typename NodeTrait<NODE_1>::NodeList::template appendList<typename NodeTrait<NODE_2>::NodeList>>;
};

template<typename COND, typename NODE_1, typename NODE_2>
struct NodeTrait<Exclusive<COND, NODE_1, NODE_2>> {
    using NodeList = typename Exclusive<COND, NODE_1, NODE_2>::NodeList;
};

#endif //TYPE_LIST_NODETRAITS_H
