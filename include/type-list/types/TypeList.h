//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_2_TYPELIST_H
#define TYPE_LIST_2_TYPELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/types/Signatures.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/TypeListConcept.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct TypeListAllSignatures
        : TypeListSignature
        , ExportableListSignature
        , AppendableSignature
{};

template <typename ... Ts>
struct TypeList : TypeListAllSignatures {
    // actually 0
    constexpr static size_t size = sizeof...(Ts);

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
struct TypeList<H, Ts...> : TypeListAllSignatures {
    using Head = H;
    using Tail = TypeList<Ts...>;
    using HeadAsType = Head;

    constexpr static size_t size = sizeof...(Ts) + 1;

    template <template <typename ...> typename RESULT>
    using exportTo = RESULT<H, Ts...>;

    template<typename ... Ts2>
    using append = TypeList<H, Ts..., Ts2...>;

    template<typename ... Ts2>
    using prepend = TypeList<Ts2..., H, Ts...>;

    template<typename T>
    using appendType = append<T>;

    template<typename T>
    using prependType = prepend<T>;

    template<ExportableTypeListConcept T>
    using appendList = typename T::template exportTo<append>;

    template<ExportableTypeListConcept T>
    using prependList = typename T::template exportTo<prepend>;
};

template<typename T>
struct RepeatTypeList : TypeListSignature, InfiniteSignature {
    using Head = T;
    using Tail = RepeatTypeList<T>;
    using HeadAsType = Head;
};

template<typename T, size_t TIMES> requires (TIMES <= 200)
struct LimitedRepeatTypeList : TypeListSignature {
    constexpr static size_t size = TIMES;
    using Head = T;
    using Tail = LimitedRepeatTypeList<T, TIMES-1>;
    using HeadAsType = Head;
};

template<typename T>
struct LimitedRepeatTypeList<T, 0> : TypeListSignature {
    constexpr static size_t size = 0;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_2_TYPELIST_H