//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODE_H
#define TYPE_LIST_NODE_H

#include <type-list/algo/Unique.h>
#include <type-list/algo/Fold.h>

struct NodeSignature {};

template<typename NODE, typename ... LINK>
struct Node : NodeSignature {
private:
    template<typename ACC, typename R>
    struct concat {
        using type = typename ACC::template appendList<R>;
    };

    using links = TYPE_LIST_NS::TypeList<typename LINK::NodeList...>;
    using decendents = __TL_FoldL(links, concat, TYPE_LIST_NS::TypeList<>);
public:
    using NodeType = NODE;
    using Decendents = TYPE_LIST_NS::Unique_tl<decendents>;

private:
    static_assert(!TYPE_LIST_NS::Elem_v<NodeType, Decendents>, "graph should not be cyclic");
};

#endif //TYPE_LIST_NODE_H
