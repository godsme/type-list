//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_2_TYPELIST_H
#define TYPE_LIST_2_TYPELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/base/Signatures.h>
#include <type-list/concept/ExportableListConcept.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct TypeListAllSignatures
        : TypeListSignature
        , ExportableListSignature
        , AppendableTypeList
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

    template<typename TYPE_LIST>
    using appendTypeList = TYPE_LIST;

    template<typename TYPE_LIST>
    using prependTypeList = TYPE_LIST;
};

template <typename H, typename ... Ts>
struct TypeList<H, Ts...> : TypeListAllSignatures {
    using Head = H;
    using Tail = TypeList<Ts...>;

    constexpr static size_t size = sizeof...(Ts) + 1;

    template <template <typename ...> typename RESULT>
    using exportTo = RESULT<H, Ts...>;

    template<typename ... Ts2>
    using append = TypeList<H, Ts..., Ts2...>;

    template<typename ... Ts2>
    using prepend = TypeList<Ts2..., H, Ts...>;

    template<ExportableListConcept TYPE_LIST>
    using appendTypeList = typename TYPE_LIST::template exportTo<append>;

    template<ExportableListConcept TYPE_LIST>
    using prependTypeList = typename TYPE_LIST::template exportTo<prepend>;
};

template<typename T>
struct RepeatTypeList : TypeListSignature, InfiniteListSignature {
    using Head = T;
    using Tail = RepeatTypeList<T>;
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_2_TYPELIST_H
