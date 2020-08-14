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

template <typename ... NODES>
struct Graph {
    using nodes = __TL_list(typename NODES::NodeType...);
    using AllNodes = __TL_unique(__TL_concat(__TL_list(nodes, typename NODES::Decendents...)));

private:
    template<typename T>
    struct NodeDecedents {
        using type = __TL_pair(typename T::NodeType, typename T::Decendents);
    };

    using NonEmptyMaps = __TL_Map(NodeDecedents, __TL_list(NODES...));

private:
    template<typename T>
    struct EmptyDecedentsNode {
        using type = __TL_pair(T, TYPE_LIST_NS::TypeList<>);
    };

    using EmptyMaps = __TL_Map(EmptyDecedentsNode, __TL_except(nodes, AllNodes));

public:
    template<typename L, typename R>
    struct LessThan {
        constexpr static bool value = \
            __TL_elem(typename L::first, typename R::second);
    };

    using SortedNodes = __TL_Sort(LessThan, typename NonEmptyMaps::template appendList<EmptyMaps>);
};

#endif //TYPE_LIST_GRAPH_H
