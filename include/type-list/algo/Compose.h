//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_COMPOSE_H
#define TYPE_LIST_COMPOSE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/concept/TypeListConcept.h>

TYPE_LIST_NS_BEGIN

__TL_lambda(Compose, typename ... OPs);

__TL_lambda(Compose, typename H, typename ... OPs)
<H, OPs...> {
public:
    template<typename INPUT>
    using apply = typename Compose<OPs...>::template apply<
            typename H::template apply<INPUT>
            >;
};

__TL_lambda(Compose, typename H)
<H> : public H {};

TYPE_LIST_NS_END

#endif //TYPE_LIST_COMPOSE_H
