//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_TRANSFORM_H
#define TYPE_LIST_TRANSFORM_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/TypeList.h>
#include <type-list/types/Value.h>
#include <type-list/types/ListWrapper.h>
#include <type-list/types/ValueList.h>
#include <type-list/types/Lambda.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Transform
            , FiniteListConcept
            , __TL_lambda_t(typename)
            , typename OUT)
    __return_t(OUT);

    __TL_lambda(Transform
       , NonEmptyFiniteListConcept IN
       , __TL_lambda_t(typename)   F
       , typename                  OUT)
    <IN, F, OUT> __return_apply_t(Transform
                    , typename IN::Tail
                    , F
                    , __TL_append_t(OUT, __TL_apply_t(F, typename IN::Head)));
}

namespace detail {
    template<__TL_lambda(F, auto), auto V>
    concept V2VConcept = requires {
        F<V>::value;
    };

    template<__TL_lambda(F, auto), auto V>
    concept V2TConcept = requires {
        typename F<V>::type;
    };

    __TL_lambda(TransformerType, __TL_lambda(F, auto),
            FiniteValueListConcept IN);

    template<__TL_lambda(F, auto), NonEmptyFiniteValueListConcept IN>
    requires V2VConcept<F, IN::Head>
    struct TransformerType<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_t(Value<__TL_apply_v(F, T::value)>);
        using type = __TL_apply_t(Transform,
                        List<IN>,
                        Mapper,
                        ValueList<>);
    };

    template<__TL_lambda(F, auto), EmptyFiniteValueListConcept IN>
    requires V2VConcept<F, 0>
    struct TransformerType<F, IN> __return_t(ValueList<>);

    template<__TL_lambda(F, auto), NonEmptyFiniteValueListConcept IN>
    requires V2TConcept<F, IN::Head>
    struct TransformerType<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_apply_t(F, T::value);
        using type = __TL_apply_t(Transform, List<IN>, Mapper, TypeList<>);
    };

    template<__TL_lambda(F, auto), EmptyFiniteValueListConcept IN>
    requires V2TConcept<F, 0>
    struct TransformerType<F, IN> __return_t(TypeList<>);
}

template<__TL_lambda(F, auto), FiniteValueListConcept IN>
using TransformValue_t = __TL_apply_t(detail::TransformerType, F, IN);

namespace detail {
   template<auto F, FiniteValueListConcept IN>
   struct V2VFTransformer {
       __TL_lambda(Mapper, __Set(T)) __return_t(Value<F(T::value)>);
       using type = __TL_apply_t(detail::Transform,
                        List<IN>,
                        Mapper,
                        ValueList<>);
   };
}

template<auto F, FiniteValueListConcept IN>
using TransformValueF_t = __TL_apply_t(detail::V2VFTransformer, F, IN);

namespace detail {
    template<typename F>
    concept T2VConcept = TypeTemplateConcept<F> && requires {
        F::template apply<int>::value;
    };

    template<typename F>
    concept T2TConcept = TypeTemplateConcept<F> && requires {
        typename F::template apply<int>::type;
    };

    template<typename F, typename IN>
    struct TypeTransformer;

    template<T2VConcept F, FiniteTypeListConcept IN>
    struct TypeTransformer<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_t(Value<F::template apply<T>::value>);
        using type = __TL_apply_t(Transform,
                         IN,
                         Mapper,
                         ValueList<>);
    };

    template<T2TConcept F, FiniteTypeListConcept IN>
    struct TypeTransformer<F, IN>
        __return_apply_t(detail::Transform, IN, F::template apply, TypeList<>);
}

template<typename F, FiniteTypeListConcept IN>
using Transform_t = __TL_apply_t(detail::TypeTransformer, F, IN);

namespace detail {
    template<FiniteListConcept IN, __TL_lambda(F, __Set())>
    auto DeductTransform() -> Transform_t<TypeTemplate<F>, IN>;

    template<FiniteListConcept IN, __TL_lambda(F, auto)>
    auto DeductTransform() -> TransformValue_t<F, IN>;

    template<FiniteListConcept IN, auto F>
    auto DeductTransform() -> TransformValueF_t<F, IN>;
}

TYPE_LIST_NS_END

#define __TL_Map(IN, F) \
decltype(TYPE_LIST_NS::detail::DeductTransform<IN, F>())

#endif //TYPE_LIST_TRANSFORM_H
