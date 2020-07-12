//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_LISTWRAPPER_H
#define TYPE_LIST_LISTWRAPPER_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/InfiniteListConcept.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<ValueListConcept LIST>
    struct ValueListWrapper : ValueListSignature {
        constexpr static size_t size = LIST::size;

        using Head = Value<LIST::Head>;
        using Tail = ValueListWrapper<typename LIST::Tail>;
    };

    template<InfiniteValueListConcept LIST>
    struct ValueListWrapper<LIST> : ValueListSignature, InfiniteListSignature {
        using Head = Value<LIST::Head>;
        using Tail = ValueListWrapper<typename LIST::Tail>;
    };

    template<typename LIST>
    struct ListTrait {
        using type = LIST;
    };

    template<ValueListConcept LIST>
    struct ListTrait<LIST> {
        using type = ValueListWrapper<LIST>;
    };
}

template <ListConcept LIST>
using List = typename detail::ListTrait<LIST>::type;

TYPE_LIST_NS_END

#endif //TYPE_LIST_LISTWRAPPER_H
