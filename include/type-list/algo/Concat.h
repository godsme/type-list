//
// Created by godsme on 8/13/20.
//

#ifndef TYPE_LIST_CONCAT_H
#define TYPE_LIST_CONCAT_H

#include <type-list/type-list-ns.h>
#include <type-list/algo/Fold.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename ACC, typename R>
    struct Concat {
        using type = typename ACC::template appendList<R>;
    };
}

template<typename TLs>
using Concat_t = __TL_FoldL(TLs, detail::Concat, TYPE_LIST_NS::TypeList<>);

TYPE_LIST_NS_END

#define __TL_concat(...) TYPE_LIST_NS::Concat_t<__VA_ARGS__>
#define __TL_concats(...) TYPE_LIST_NS::Concat_t<TYPE_LIST_NS::TypeList<__VA_ARGS__>>

#endif //TYPE_LIST_CONCAT_H
