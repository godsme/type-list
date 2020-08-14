//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODECB_H
#define TYPE_LIST_NODECB_H

#include <cstdint>

using actor_handle = intptr_t;

template<typename T>
struct NodeCB {
    actor_handle actorHandle;
};

#endif //TYPE_LIST_NODECB_H
