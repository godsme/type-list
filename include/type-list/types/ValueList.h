//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_VALUELIST_H
#define TYPE_LIST_VALUELIST_H

#include <type-list/type-list-ns.h>
#include <type-list/types/Signatures.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/types/Value.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct ValueListAllSignatures
   : ValueListSignature
   , ExportableListSignature
   , AppendableSignature
{};

template<auto ... Vs>
struct ValueList : ValueListAllSignatures {
    constexpr static size_t size = sizeof...(Vs);

    template <template <auto ...> typename RESULT>
    using exportTo = RESULT<Vs...>;

    template<auto ... Vs2>
    using append = ValueList<Vs..., Vs2...>;

    template<auto ... Vs2>
    using prepend = ValueList<Vs2..., Vs...>;

    template<typename T>
    using appendType = append<T::value>;

    template<typename T>
    using prependType = prepend<T::value>;

    template<ValueListConcept T>
    using appendList = T;

    template<ValueListConcept T>
    using prependList = T;
};

template<auto H, auto ... Vs>
struct ValueList<H, Vs...> : ValueListAllSignatures {
    constexpr static size_t size = sizeof...(Vs) + 1;

    constexpr static auto Head = H;
    using Tail = ValueList<Vs...>;
    using HeadAsType = Value<Head>;

    template <template <auto ...> typename RESULT>
    using exportTo = RESULT<H, Vs...>;

    template<auto ... Vs2>
    using append = ValueList<H, Vs..., Vs2...>;

    template<auto ... Vs2>
    using prepend = ValueList<Vs2..., H, Vs...>;

    template<typename T>
    using appendType = append<T::value>;

    template<typename T>
    using prependType = prepend<T::value>;

    template<ExportableValueListConcept T>
    using appendList = typename T::template exportTo<append>;

    template<ExportableValueListConcept T>
    using prependList = typename T::template exportTo<prepend>;
};

////////////////////////////////////////////////////////////////////
template<auto INIT, auto STEP = 1>
struct InfiniteIntList : ValueListSignature, InfiniteSignature {
    constexpr static auto Head = INIT;
    using HeadAsType = Value<Head>;
    using Tail = InfiniteIntList<INIT+STEP, STEP>;
};

template<auto V>
struct RepeatValueList : ValueListSignature, InfiniteSignature {
    constexpr static auto Head = V;
    using HeadAsType = Value<Head>;
    using Tail = RepeatValueList<V>;
};

template<auto V, size_t times>
struct LimitedRepeatValueList : ValueListSignature {
    constexpr static size_t size = times;

    constexpr static auto Head = V;
    using Tail = LimitedRepeatValueList<V, times - 1>;

    using HeadAsType = Value<Head>;
};

template<auto V>
struct LimitedRepeatValueList<V, 0> : ValueListSignature {
    constexpr static size_t size = 0;
};

TYPE_LIST_NS_END

#define __TL_infinite(...) TYPE_LIST_NS::InfiniteIntList<__VA_ARGS__>

#endif //TYPE_LIST_VALUELIST_H
