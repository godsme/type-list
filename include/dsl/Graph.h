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
    static_assert(nodes::size == __TL_unique(nodes)::size, "duplicated nodes");

    using AllNodes = __TL_unique(__TL_concat(__TL_list(nodes, typename NODES::Decendents...)));
    using SortedNodes = typename NodesSort<NODES...>::sortedNodes;
    static_assert(NodesSort<NODES...>::allDecedentsOfRoot::size == (SortedNodes::size - 1), "unreachable nodes exists");
};

#define __graph(...) Graph<__VA_ARGS__>

#endif //TYPE_LIST_GRAPH_H
