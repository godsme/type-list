//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_2_TYPELIST_H
#define TYPE_LIST_2_TYPELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/types/Signatures.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/concept/TypeListConcept.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct TypeListAllSignatures
        : detail::ListSignature
        , detail::TypeListSignature
        , detail::ExportableListSignature
        , detail::AppendableSignature
{};

template<typename ... Ts>
struct TypeListBase : TypeListAllSignatures {
    constexpr static size_t size = sizeof...(Ts);
};

template <typename ... Ts>
struct TypeList : TypeListBase<Ts...> {
    template <template <typename ...> typename RESULT>
    using exportTo = RESULT<Ts...>;

    template<typename ... Ts2>
    using append = TypeList<Ts..., Ts2...>;

    template<typename ... Ts2>
    using prepend = TypeList<Ts2...,  Ts...>;

    template<typename T>
    using appendType = append<T>;

    template<typename T>
    using prependType = prepend<T>;

    template<TypeListConcept T>
    using appendList = T;

    template<TypeListConcept T>
    using prependList = T;
};

template <typename H, typename ... Ts>
struct TypeList<H, Ts...> : TypeListBase<H, Ts...> {
    using Head = H;
    using Tail = TypeList<Ts...>;
    using HeadAsType = Head;

    template <template <typename ...> typename RESULT>
    static auto exportTo() -> RESULT<H, Ts...>;

    template<typename ... Ts2>
    using append = TypeList<H, Ts..., Ts2...>;

    template<typename ... Ts2>
    using prepend = TypeList<Ts2..., H, Ts...>;

    template<typename T>
    using appendType = append<T>;

    template<typename T>
    using prependType = prepend<T>;

    template<ExportableTypeListConcept T>
    using appendList = decltype(T::template exportTo<append>());

    template<FiniteTypeListConcept T>
    using prependList = decltype(T::template exportTo<prepend>());
};

template<typename T>
struct RepeatTypeList
        : detail::ListSignature
        , detail::TypeListSignature
        , detail::InfiniteSignature {
    using Head = T;
    using Tail = RepeatTypeList<T>;
    using HeadAsType = Head;
};

template<typename T, size_t TIMES> requires (TIMES <= 200)
struct LimitedRepeatTypeList : TypeListAllSignatures {
    constexpr static size_t size = TIMES;
    using Head = T;
    using Tail = LimitedRepeatTypeList<T, TIMES-1>;
    using HeadAsType = Head;
};

template<typename T>
struct LimitedRepeatTypeList<T, 0> : TypeListAllSignatures {
    constexpr static size_t size = 0;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_2_TYPELIST_H
