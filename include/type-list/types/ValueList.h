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
#include <type-list/types/TypeList.h>
#include <cstddef>

TYPE_LIST_NS_BEGIN

struct ValueListAllSignatures
   : detail::ListSignature
   , detail::ValueListSignature
   , detail::ExportableListSignature
   , detail::AppendableSignature
{};

template<auto ... Vs>
struct ValueListBase : ValueListAllSignatures {
    constexpr static size_t size = sizeof...(Vs);
};

template<auto ... Vs>
struct ValueList : ValueListBase<Vs...> {

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

namespace detail {
    template<typename LIST, auto ... Vs>
    struct ToTypeList {
        using type = LIST;
    };

    template<typename LIST, auto H, auto ... Vs>
    struct ToTypeList<LIST, H, Vs...> {
        using type = \
        typename ToTypeList<typename LIST::template appendType<Value<H>>, Vs...>::type;
    };
}

template<auto H, auto ... Vs>
struct ValueList<H, Vs...> : ValueListBase<H, Vs...> {
    constexpr static auto Head = H;
    using Tail = ValueList<Vs...>;
    using HeadAsType = Value<Head>;

    template <template <auto ...> typename RESULT>
    static auto exportTo() -> RESULT<H, Vs...>;

    template<auto ... Vs2>
    using append = ValueList<H, Vs..., Vs2...>;

    template<auto ... Vs2>
    using prepend = ValueList<Vs2..., H, Vs...>;

    template<typename T>
    using appendType = append<T::value>;

    template<typename T>
    using prependType = prepend<T::value>;

    template<ExportableValueListConcept T>
    using appendList = decltype(T::template exportTo<append>());

    template<ExportableValueListConcept T>
    using prependList = decltype(T::template exportTo<prepend>());
};

////////////////////////////////////////////////////////////////////
template<auto INIT, auto STEP = 1>
struct InfiniteIntList
        : detail::ListSignature
        , detail::ValueListSignature
        , detail::InfiniteSignature {
    constexpr static auto Head = INIT;
    using HeadAsType = Value<Head>;
    using Tail = InfiniteIntList<INIT+STEP, STEP>;
};

template<auto V>
struct RepeatValueList
        : detail::ListSignature
        , detail::ValueListSignature
        , detail::InfiniteSignature {
    constexpr static auto Head = V;
    using HeadAsType = Value<Head>;
    using Tail = RepeatValueList<V>;
};

namespace detail {
    template<auto V, size_t TIMES, auto ... Vs>
    struct RepeatValueGenerator {
        using type = typename RepeatValueGenerator<V, TIMES-1, Vs..., V>::type;
    };

    template<auto V, auto ... Vs>
    struct RepeatValueGenerator<V, 0, Vs...> {
        using type = ValueList<Vs...>;
    };
}
template<auto V, size_t TIMES> requires (TIMES <= 200)
class LimitedRepeatValueList : ValueListAllSignatures {
    using list = typename detail::RepeatValueGenerator<V, TIMES>::type;
public:
    constexpr static size_t size = TIMES;

    constexpr static auto Head = V;
    using Tail = LimitedRepeatValueList<V, TIMES - 1>;

    using HeadAsType = Value<Head>;

    template <template <auto ...> typename RESULT>
    static auto exportTo() -> decltype(list::template exportTo<RESULT>());

    template<auto ... Vs2>
    using append = typename list::template append<Vs2...>;

    template<auto ... Vs2>
    using prepend = typename list::template prepend<Vs2...>;

    template<ExportableValueListConcept T>
    using appendList = decltype(T::template exportTo<append>());

    template<FiniteValueListConcept T>
    using prependList = decltype(T::template exportTo<prepend>());
};

template<auto V>
struct LimitedRepeatValueList<V, 0> : ValueList<> {
};

TYPE_LIST_NS_END

#endif //TYPE_LIST_VALUELIST_H
