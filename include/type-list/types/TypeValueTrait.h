//
// Created by godsme on 7/19/20.
//

#ifndef TYPE_LIST_TYPEVALUETRAIT_H
#define TYPE_LIST_TYPEVALUETRAIT_H

#include <type-list/type-list-ns.h>
#include <type-list/types/Value.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename T>
    concept HasValue = requires {
        T::value;
    };

    template<typename T>
    concept HasType = requires {
        typename T::type;
    };

    template<typename T>
    struct ValueTypeTrait;

    template<HasType T>
    struct ValueTypeTrait<T> {
        using type = typename T::type;
    };

    template<HasValue T>
    struct ValueTypeTrait<T> {
        using type = Value<T::value>;
    };
}

TYPE_LIST_NS_END

#endif //TYPE_LIST_TYPEVALUETRAIT_H
