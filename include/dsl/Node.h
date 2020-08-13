//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODE_H
#define TYPE_LIST_NODE_H

#include <type-list/algo/Unique.h>
#include <type-list/algo/Fold.h>
#include <type-list/algo/Concat.h>

struct NodeSignature {};

template<typename NODE, typename ... LINK>
struct Node : NodeSignature {
    using NodeType = NODE;
    using Decendents = __TL_unique(__TL_concat(__TL_list(typename LINK::NodeList...)));
private:
    static_assert(!__TL_elem(NodeType, Decendents), "graph should not be cyclic");
};

#endif //TYPE_LIST_NODE_H
