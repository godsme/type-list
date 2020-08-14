//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_GRAPH_H
#define TYPE_LIST_GRAPH_H

#include <dsl/Node.h>
#include <type_traits>
#include <type-list/algo/Transform.h>
#include <type-list/types/Pair.h>
#include <type-list/algo/Except.h>
#include <type-list/algo/Sort.h>
#include <dsl/NodesSort.h>

template <typename ... NODES>
struct Graph {
    using nodes = __TL_list(typename NODES::NodeType...);
    using AllNodes = __TL_unique(__TL_concat(__TL_list(nodes, typename NODES::Decendents...)));
    using SortedNodes = typename NodesSort<NODES...>::sortedNodes;
};

#define __graph(...) Graph<__VA_ARGS__>

#endif //TYPE_LIST_GRAPH_H
