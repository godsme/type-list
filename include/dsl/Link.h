//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_LINK_H
#define TYPE_LIST_LINK_H

#include <dsl/NodeTraits.h>

template<typename T>
struct Link;

template<typename PORT, typename NODE_LIST>
struct Link<auto (PORT) -> NODE_LIST> {
    using PortType = PORT;
    using NodeList = typename NodeTrait<NODE_LIST>::NodeList;
};

#endif //TYPE_LIST_LINK_H
