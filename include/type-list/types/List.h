//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LIST_H
#define TYPE_LIST_LIST_H

#include <type-list/types/TypeList.h>
#include <type-list/types/ValueList.h>
#include <type-list/concept/NonEmptyListConcept.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    template<typename T>
    struct EmptyValueWrapperTrait {
        using type = TypeList<T>;
    };

    template<typename T> requires std::is_base_of_v<ValueSignature, T>
    struct EmptyValueWrapperTrait<T> {
        using type = ValueList<T::value>;
    };
}

struct EmptyList
        : ListSignature
        , TypeListSignature
        , ValueListSignature
        , AppendableSignature {
    constexpr static size_t size = 0;

    template <template <auto ...> typename RESULT>
    auto exportTo() -> RESULT<>;

    template <template <typename ...> typename RESULT>
    auto exportTo() -> RESULT<>;

    template<ListConcept T>
    using appendList = T;

    template<ListConcept T>
    using prependList = T;

    template<typename T>
    using appendType = typename detail::EmptyValueWrapperTrait<T>::type;
};

namespace detail {
    template<ListConcept T>
    struct EmptyListTrait {
        using type = T;
    };

    template<EmptyListConcept T>
    struct EmptyListTrait<T> {
        using type = EmptyList;
    };
}

namespace detail {

    template<int, typename T, typename ... Ts>
    auto DeduceListType() -> TypeList<T, Ts...>;

    template <int>
    auto DeduceListType() -> EmptyList;

    template<int, auto V, auto ... Vs>
    auto DeduceListType() -> ValueList<V, Vs...>;

    template<typename T>
    auto DeduceRepeatListType() -> RepeatTypeList<T>;

    template<auto V>
    auto DeduceRepeatListType() -> RepeatValueList<V>;

    template<auto V, size_t TIMES>
    auto DeduceRepeatListType() -> LimitedRepeatValueList<V, TIMES>;

    template<typename T, size_t TIMES>
    auto DeduceRepeatListType() -> LimitedRepeatTypeList<T, TIMES>;
}

TYPE_LIST_NS_END

#define __TL_list(...) \
decltype(TYPE_LIST_NS::detail::DeduceListType<0, ##__VA_ARGS__>())

#define __TL_repeat(p, ...) \
decltype(TYPE_LIST_NS::detail::DeduceRepeatListType<p, ##__VA_ARGS__>())

#define __TL_infinite(...) TYPE_LIST_NS::InfiniteIntList<__VA_ARGS__>

#endif //TYPE_LIST_LIST_H
