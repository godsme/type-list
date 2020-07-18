//
// Created by godsme on 7/17/20.
//

#ifndef TYPE_LIST_COMPOSE_H
#define TYPE_LIST_COMPOSE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/concept/TypeListConcept.h>
#include <type-list/concept/CallableConcept.h>
#include <type-list/types/TemplateDeduce.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Compose, CallableConcept ... OPs);
    __TL_lambda(Compose, CallableConcept LAST)
            <LAST> : public LAST {};
    __TL_lambda(Compose, CallableConcept H, CallableConcept ... OPs)
            <H, OPs...> __return_callable(typename INPUT,
                                          __TL_call(Compose<OPs...>, __TL_call(H, INPUT)));
}

namespace detail {
    template<CallableConcept H, size_t SIZE, typename ... OPs>
    struct DoCompose {
        template<typename ... INPUT>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, INPUT...));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 1, OPs...> {
        template<typename T>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 2, OPs...> {
        template<typename T1, typename T2>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 3, OPs...> {
        template<typename T1, typename T2, typename T3>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 4, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 5, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4, typename T5>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4, T5));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 6, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4, T5, T6));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 7, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4, T5, T6, T7));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 8, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4, T5, T6, T7, T8));
    };

    template<CallableConcept H, typename ... OPs>
    struct DoCompose<H, 9, OPs...> {
        template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
        using apply = __TL_call(detail::Compose<OPs...>, __TL_call(H, T1, T2, T3, T4, T5, T6, T7, T8, T9));
    };
}

template<CallableConcept H, CallableConcept ... OPs>
using Compose = detail::DoCompose<H, __DEDUCE_TEMPLATE_ARGS(H::template apply)::value, OPs...>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_COMPOSE_H
