//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_EMPTYLIST_H
#define TYPE_LIST_EMPTYLIST_H

#include <type-list/types/Signatures.h>
#include <type-list/types/TypeList.h>
#include <type-list/types/ValueList.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/Value.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    ///////////////////////////////////////////////////////////////////
    __TL_lambda(EmptyValueWrapperTrait, typename T)
    __return_t(TypeList<T>);

    __TL_lambda(EmptyValueWrapperTrait, ValueConcept T)
            <T> __return_t(ValueList<T::value>);

    ///////////////////////////////////////////////////////////////////
    __TL_lambda(ToValueList, typename LIST, typename ... Ts)
    __return_t(LIST);

    __TL_lambda(ToValueList, typename LIST, typename H, typename ... Ts)
            <LIST, H, Ts...>
    __return_t(typename LIST::template append<H::value>);

    ///////////////////////////////////////////////////////////////////
    __TL_lambda(AppendTrait, typename ... Ts)
    __return_t(void);

    __TL_lambda(AppendTrait, ValueConcept H, typename ... Ts)
            <H, Ts...> __return_t(__TL_apply(ToValueList, ValueList<>, Ts...));

    __TL_lambda(AppendTrait, typename H, typename ... Ts)
            <H, Ts...> __return_t(__TL_apply(TypeList, H, Ts...));

}

struct EmptyList
        : detail::ListSignature
        , detail::ExportableListSignature
        , detail::TypeListSignature
        , detail::ValueListSignature
        , detail::AppendableSignature {
    constexpr static size_t size = 0;
    using origin = ValueList<>;

    template <template <auto ...> typename RESULT>
    static auto exportTo() -> RESULT<>;

    template <template <typename ...> typename RESULT>
    static auto exportTo() -> RESULT<>;

    template<ListConcept T>
    using appendList = T;

    template<ListConcept T>
    using prependList = T;

    template<typename ... Ts>
    using append = std::conditional_t<sizeof...(Ts) == 0,
            EmptyList,
            typename detail::AppendTrait<Ts...>::type>;

    template<typename ... Ts>
    using prepend = append<Ts...>;

    template<typename T>
    using appendType = typename detail::EmptyValueWrapperTrait<T>::type;

    template<typename T>
    using prependType = typename detail::EmptyValueWrapperTrait<T>::type;
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

TYPE_LIST_NS_END

#endif //TYPE_LIST_EMPTYLIST_H
