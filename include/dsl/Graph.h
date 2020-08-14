//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_GRAPH_H
#define TYPE_LIST_GRAPH_H

#include <dsl/Node.h>
#include <dsl/NodeCB.h>
#include <type_traits>
#include <type-list/algo/Transform.h>
#include <type-list/types/Pair.h>
#include <type-list/algo/Except.h>
#include <type-list/algo/Sort.h>
#include <dsl/NodesSort.h>

template <typename ... NODES>
struct Graph {
    using Nodes = __TL_list(typename NODES::NodeType...);
    using SortedNodes = typename NodesSort<NODES...>::sortedNodes;

private:
    static_assert(Nodes::size == __TL_unique(Nodes)::size, "duplicated nodes");
    static_assert(NodesSort<NODES...>::allDecedentsOfRoot::size == (SortedNodes::size - 1), "unreachable nodes exist");

private:
    template<typename ... Ts>
    using CBs = std::tuple<NodeCB<Ts>...>;

    using NodeControlBlock = decltype(SortedNodes::template exportTo<CBs>());

private:
    NodeControlBlock nodeControlBlocks;
};

#define __graph(...) Graph<__VA_ARGS__>

#endif //TYPE_LIST_GRAPH_H
