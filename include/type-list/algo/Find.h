//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_FIND_H
#define TYPE_LIST_FIND_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/Value.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename T, template<typename, typename > typename PRED, typename = void, typename ... Ts>
    struct Find {
        using type = void;
    };

    template<typename T, template<typename, typename > typename PRED, typename H, typename ... Ts>
    struct Find<T, PRED, std::enable_if_t<PRED<T, H>::value>, H, Ts...> {
        using type = H;
    };

    template<typename T, template<typename, typename > typename PRED, typename H, typename ... Ts>
    struct Find<T, PRED, std::enable_if_t<!PRED<T, H>::value>, H, Ts...> {
        using type = typename Find<T, PRED, void, Ts...>::type;
    };
}

template<typename T, template<typename, typename> typename PRED, typename TL>
struct Find {
    template<typename ... Ts>
    using find = typename detail::Find<T, PRED, void, Ts...>::type;

    using type = decltype(TL::template exportTo<find>());
};

template<typename T, template<typename, typename> typename PRED, typename TL>
using Find_t = typename Find<T, PRED, TL>::type;

TYPE_LIST_NS_END

#endif //TYPE_LIST_FIND_H
