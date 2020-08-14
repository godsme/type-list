//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_NODESSORT_H
#define TYPE_LIST_NODESSORT_H

#include <dsl/Node.h>
#include <type_traits>
#include <type-list/algo/Transform.h>
#include <type-list/types/Pair.h>
#include <type-list/algo/Except.h>
#include <type-list/algo/Sort.h>
#include <type-list/types/Map.h>
#include <type-list/algo/Reserve.h>

template<typename ... NODES>
struct NodesSort {
private:
    using nodes = __TL_list(typename NODES::NodeType...);
    using AllNodes = __TL_unique(__TL_concat(__TL_list(nodes, typename NODES::Decendents...)));

    template<typename T>
    struct NodeDecedents {
        using type = __TL_pair(typename T::NodeType, typename T::Decendents);
    };

    using NonEmptyMaps = __TL_Map(NodeDecedents, __TL_list(NODES...));

private:
    template<typename T>
    struct EmptyDecedentsNode {
        using type = __TL_pair(T, __TL_list());
    };

    using EmptyMaps = __TL_Map(EmptyDecedentsNode, __TL_except(nodes, AllNodes));

    using ThisMap = typename NonEmptyMaps::template appendList<EmptyMaps>;

    template<typename TL, typename T>
    struct AllDecedents {
        using decedents = __TL_map_find(T, ThisMap, __TL_list());
        using type = typename TL::template appendType<T>::template appendList<__TL_FoldL(decedents, AllDecedents, __TL_list())>;
    };

    template<typename E>
    struct ToAllDecedents {
        using result = __TL_unique(typename E::second::template appendList<__TL_FoldL(typename E::second, AllDecedents, __TL_list())>);
        using type = __TL_pair(typename E::first, result);
    };

    using AllDecedentsMap = __TL_Map(ToAllDecedents, ThisMap);

    template<typename L, typename R>
    struct IsDecedentOf {
        constexpr static bool value = \
            __TL_elem(typename L::first, typename R::second);
    };

    using sortResult = __TL_reverse(__TL_Sort(IsDecedentOf, AllDecedentsMap));

    template<typename T>
    struct ToDirectDecedents {
        using decedents = __TL_map_find(typename T::first, ThisMap, __TL_list());
        using type = __TL_pair(typename T::first, decedents);
    };

    template<typename T>
    struct ToNode {
        using type = typename T::first;
    };

public:
    using result = __TL_Map(ToDirectDecedents, sortResult);
    using sortedNodes = __TL_Map(ToNode, sortResult);
    using allDecedentsOfRoot = typename sortResult::Head::second;
};

#endif //TYPE_LIST_NODESSORT_H
