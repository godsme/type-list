//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_MAP_H
#define TYPE_LIST_MAP_H

#include <type-list/types/Signatures.h>
#include <type-list/types/TypeList.h>
#include <type-list/types/Pair.h>
#include <type-list/algo/Find.h>

TYPE_LIST_NS_BEGIN

template<typename K, typename V>
using Map = TypeList<Pair<K, V>>;

template<typename T, typename>
struct MapValue {
    using type = typename T::second;
};

template<typename DEFAULT>
struct MapValue<void, DEFAULT> {
    using type = DEFAULT;
};

template <typename MAP, typename K, typename DEFAULT>
struct FindInMap {
    template<typename T, typename E>
    struct Match {
        constexpr static bool value = std::is_same_v<T, typename E::first>;
    };

    using type = typename MapValue<Find_t<K, Match, MAP>, DEFAULT>::type;
};

template <typename K, typename MAP, typename DEFAULT>
using MapFind_t = typename FindInMap<MAP, K, DEFAULT>::type;

TYPE_LIST_NS_END

#endif //TYPE_LIST_MAP_H
