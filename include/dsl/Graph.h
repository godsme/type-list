//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_GRAPH_H
#define TYPE_LIST_GRAPH_H

#include <dsl/Node.h>
#include <type_traits>

template <typename = void, typename ... NODES>
struct Graph;

template<typename ... NODES>
struct Graph<std::enable_if_t<(std::is_base_of_v<NodeSignature, NODES> && ...)>, NODES...> {
    //using AllNodes = TYPE_LIST_NS::TypeList<NODES..., >
};

#endif //TYPE_LIST_GRAPH_H
