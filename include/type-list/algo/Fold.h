//
// Created by godsme on 7/18/20.
//

#ifndef TYPE_LIST_FOLD_H
#define TYPE_LIST_FOLD_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/types/Value.h>
#include <type-list/algo/Curry.h>
#include <type-list/algo/Filter.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ... IN);
    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ACC)
    <F, ACC> __return_t(ACC);

    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ACC, typename H, typename ... IN)
    <F, ACC, H, IN...>
    __return_apply_t(FoldL, F, __TL_apply_t(F, ACC, H), IN...);

namespace detail {
    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), typename ... IN);
    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), typename LAST)
    <F, LAST> __return_t(LAST);

    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), typename H, typename ... IN)
    <F, H, IN...> __return_apply_t(F, H, __TL_apply_t(FoldR, F, IN...));
}

TYPE_LIST_NS_END

#endif //TYPE_LIST_FOLD_H
