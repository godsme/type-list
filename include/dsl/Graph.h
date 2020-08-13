//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_GRAPH_H
#define TYPE_LIST_GRAPH_H

#include <dsl/Node.h>
#include <type_traits>

template <typename ... NODES>
struct Graph {
    using nodes = __TL_list(typename NODES::NodeType...);
    using AllNodes = __TL_unique(__TL_concat(__TL_list(nodes, typename NODES::Decendents...)));
};

#endif //TYPE_LIST_GRAPH_H
