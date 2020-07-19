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
#include <type-list/types/TypeValueTrait.h>
#include <cstdint>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ACC, typename IN);
    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ACC, EmptyListConcept IN)
    <F, ACC, IN> __return_t(ACC);

    __TL_lambda(FoldL, __TL_lambda(F, typename, typename), typename ACC, NonEmptyListConcept IN)
    <F, ACC, IN> __return_apply_t(FoldL, F, __TL_apply_t(detail::ValueTypeTrait, __TL_apply(F, ACC, typename IN::Head)), typename IN::Tail);
}

namespace detail {
    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), typename IN, typename = void);
    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), NonEmptyListConcept IN)
    <F, IN, std::enable_if_t<IN::size == 1>>
            __return_t(typename IN::Head);

    __TL_lambda(FoldR, __TL_lambda(F, typename, typename), NonEmptyListConcept IN)
    <F, IN, std::enable_if_t<(IN::size > 1)>>
            __return_apply_t(detail::ValueTypeTrait, F<__TL_apply_t(FoldR, F, typename IN::Tail), typename IN::Head>);
}

namespace detail {
    __TL_lambda(FoldTrait, bool L = true) {
    public:
        template<__TL_lambda(F, typename, typename), typename IN>
        using apply = typename FoldL<F, typename IN::Head, typename IN::Tail>::type;
    };

    __TL_lambda(FoldTrait)
    <false> {
    public:
        template<__TL_lambda(F, typename, typename), typename IN>
        using apply = typename FoldR<F, IN>::type;
    };

    __TL_lambda(FoldType, bool L, typename F, typename IN);
    __TL_lambda(FoldType, bool L, TypeTemplateConcept F, typename IN)
    <L, F, IN> __return_t(__TL_apply(FoldTrait<L>::template apply, F::template apply, IN));

    __TL_lambda(FoldType, bool L, ValueTemplateConcept F, typename IN)
    <L, F, IN> {
        __TL_lambda(Acc, __Set(T1), __Set(T2)) __return_t(Value<__TL_call_v(F, T1::value, T2::value)>);
        __result_t(__TL_apply(FoldTrait<L>::template apply, Acc, IN));
    };

    __TL_lambda(FoldType, bool L, ValueConcept F, typename IN)
    <L, F, IN> {
        __TL_lambda(Acc, __Set(T1), __Set(T2)) __return_t(Value<F::value(T1::value, T2::value)>);
        __result_t(__TL_apply(FoldTrait<L>::template apply, Acc, IN));
    };
}

namespace detail {
    __TL_lambda(FoldListTrait, bool L, typename INIT, typename LIST);
    __TL_lambda(FoldListTrait, bool L, typename LIST)
    <L, void, LIST> __return_t(LIST);

    __TL_lambda(FoldListTrait, typename INIT, typename LIST)
    <true, INIT, LIST> __return_t(typename LIST::template prependType<INIT>);

    __TL_lambda(FoldListTrait, typename INIT, typename LIST)
    <false, INIT, LIST> __return_t(typename LIST::template appendType<INIT>);
}

namespace detail {
    __TL_lambda(DoFold, bool L, typename F, FiniteListConcept IN, typename INIT){
        using list = __TL_apply_t(detail::FoldListTrait, L, INIT, List<IN>);
        __result_t(__TL_apply_t(detail::FoldType, L, F, List<list>));
    };
}

template<bool L, typename F, FiniteListConcept IN, typename INIT>
using Fold_t = __TL_apply_t(detail::DoFold, L, F, IN, INIT);

namespace detail {
    constexpr uint64_t __stupid_secrete_nothing = 0xabcd'ef01'2345'6789;

    template<auto V> struct __value_trait { using type = Value<V>; };
    template<> struct __value_trait<__stupid_secrete_nothing> { using type = void; };

    template<__TL_lambda(F, typename, auto)>
    struct Value2TypeAcc : TypeCallableSignature {
        template<typename T1, typename T2>
        using apply = F<T1, T2::value>;
    };

    template<__TL_lambda(F, auto, typename)>
    struct Type2ValueAcc : TypeCallableSignature {
        template<typename T1, typename ... Ts>
        using apply = F<T1::value, Ts...>;
    };

    template<bool L, typename IN, __TL_lambda(F, auto, typename), auto INIT = __stupid_secrete_nothing>
    auto deduceFold() -> Fold_t<L, Type2ValueAcc<F>, IN, __TL_apply_t(__value_trait, INIT)>;

    template<bool L, typename IN, __TL_lambda(F, auto, auto), auto INIT = __stupid_secrete_nothing>
    auto deduceFold() -> Fold_t<L, __TL_toType(F), IN, __TL_apply_t(__value_trait, INIT)>;

    template<bool L, typename IN, auto F, auto INIT = __stupid_secrete_nothing>
    auto deduceFold() -> Fold_t<L, __TL_toType(F), IN, __TL_apply_t(__value_trait, INIT)>;

    template<bool L, typename IN, __TL_lambda(F, typename, auto), typename INIT = void>
    auto deduceFold() -> Fold_t<L, Value2TypeAcc<F>, IN, INIT>;

    template<bool L, typename IN, __TL_lambda(F, typename, typename), typename INIT = void>
    auto deduceFold() -> Fold_t<L, __TL_toType(F), IN, INIT>;
}

TYPE_LIST_NS_END

#define __TL_FoldL(...) \
decltype(TYPE_LIST_NS::detail::deduceFold<true, __VA_ARGS__>())

#endif //TYPE_LIST_FOLD_H
