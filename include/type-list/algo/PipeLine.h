//
// Created by godsme on 7/15/20.
//

#ifndef TYPE_LIST_PIPELINE_H
#define TYPE_LIST_PIPELINE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/concept/TypeListConcept.h>
#include <type-list/algo/Sort.h>
#include <type-list/algo/Take.h>
#include <type-list/algo/Drop.h>
#include <type-list/algo/Filter.h>
#include <type-list/algo/Transform.h>
#include <type-list/algo/Curry.h>
#include <type-list/algo/Compose.h>

TYPE_LIST_NS_BEGIN

#define __TL_take(...) __TL_curry_t(TYPE_LIST_NS::Take_t, TYPE_LIST_NS::Value<__VA_ARGS__>)
#define __TL_drop(...) __TL_curry_t(TYPE_LIST_NS::Drop_t, TYPE_LIST_NS::Value<__VA_ARGS__>)
#define __TL_filter(...) __TL_curry_t(TYPE_LIST_NS::Filter_t, __TL_toType((__VA_ARGS__)))
#define __TL_sort(...) __TL_curry_t(TYPE_LIST_NS::Sort_t, __TL_toType((__VA_ARGS__)))
#define __TL_map(...) __TL_curry_t(TYPE_LIST_NS::Transform_t, __TL_toType((__VA_ARGS__)))

/////////////////////////////////////////////////////////////////////////////////////////
template<typename IN, typename H, typename ... OPs>
struct PipeLine final {
    using type = typename Compose<H, OPs...>::template apply<IN>;
};

TYPE_LIST_NS_END

#define __TL_pipeline(list, ...) \
__TL_apply_t(TYPE_LIST_NS::PipeLine, list, __VA_ARGS__)

#endif //TYPE_LIST_PIPELINE_H
