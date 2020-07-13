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
    template< FiniteListConcept, __TL_lambda_t(typename), typename OUT>
    struct Transform __return_t(OUT);

    template
       < NonEmptyFiniteListConcept IN
       , __TL_lambda_t(typename)    F
       , typename                  OUT>
    __TL_pattern(Transform, IN, F, OUT)
    __return_apply_t(Transform
            , __Set(IN::Tail)
            , F
            , __TL_append_t(OUT, __TL_apply_t(F, typename IN::Head)));
}

namespace detail {
    template<__TL_lambda(F, auto)>
    struct V2VAdapter {
        __TL_lambda(Mapper, __Set(T))
        __return_t(Value<__TL_apply_v(F, T::value)>);
    };

    template<__TL_lambda(F, auto)>
    struct V2TAdapter {
        __TL_lambda(Mapper, __Set(T))
        __return_apply_t(F, T::value);
    };

    template<__TL_lambda(F, auto), auto V>
    concept V2VConcept = requires {
        F<V>::value;
    };

    template<__TL_lambda(F, auto), auto V>
    concept V2TConcept = requires {
        typename F<V>::type;
    };

    __TL_lambda(ValueTransformer,
            FiniteValueListConcept IN, __TL_lambda(F, auto));

    template<NonEmptyFiniteValueListConcept IN, __TL_lambda(F, auto)>
    requires V2VConcept<F, IN::Head>
    struct ValueTransformer<IN, F>
    __return_apply_t(detail::Transform
                , List<IN>
                , V2VAdapter<F>::template Mapper
                , ValueList<>);

    template<EmptyFiniteValueListConcept IN, __TL_lambda(F, auto)>
    requires V2VConcept<F, 0>
    struct ValueTransformer<IN, F> __return_t(ValueList<>);

    template<NonEmptyFiniteValueListConcept IN, __TL_lambda(F, auto)>
    requires V2TConcept<F, IN::Head>
    struct ValueTransformer<IN, F>
    __return_apply_t(detail::Transform
            , List<IN>
            , V2TAdapter<F>::template Mapper
            , TypeList<>);

    template<EmptyFiniteValueListConcept IN, __TL_lambda(F, auto)>
    requires V2TConcept<F, 0>
    struct ValueTransformer<IN, F> __return_t(TypeList<>);
}

template<FiniteValueListConcept IN, __TL_lambda(F, auto)>
using TransformValue_t = __TL_apply_t(detail::ValueTransformer, IN, F);

namespace detail {
   template<auto F>
   struct V2VFMapper {
      __TL_lambda(Mapper, __Set(T)) __return_t(Value<F(T::value)>);
   };

   template<FiniteValueListConcept IN, auto F>
   struct V2VFTransformer
   __return_apply_t(detail::Transform,
                           List<IN>,
                           V2VFMapper<F>::template Mapper,
                           ValueList<>);
}

template<FiniteValueListConcept IN, auto F>
using TransformValueF_t = __TL_apply_t(detail::V2VFTransformer, IN, F);

namespace detail {
    template<__TL_lambda(F, typename)>
    struct T2VAdapter {
        __TL_lambda(Mapper, __Set(T)) __return_t(Value<F<T>::value>);
    };

    template<__TL_lambda(F, typename)>
    concept T2VConcept = requires {
        F<int>::value;
    };

    template<__TL_lambda(F, typename)>
    concept T2TConcept = requires {
        typename F<int>::type;
    };

    template<FiniteTypeListConcept IN, __TL_lambda(F, __Set())>
    struct TypeTransformer;

    template<FiniteTypeListConcept IN, __TL_lambda(F, __Set())>
    requires T2VConcept<F>
    struct TypeTransformer<IN, F>
    __return_apply_t(detail::Transform,
                            IN,
                            T2VAdapter<F>::template Mapper,
                            ValueList<>);

    template<FiniteTypeListConcept IN, __TL_lambda(F, __Set())>
    requires T2TConcept<F>
    struct TypeTransformer<IN, F>
    __return_apply_t(detail::Transform, IN, F, TypeList<>);
}

template<FiniteTypeListConcept IN, __TL_lambda(F, __Set())>
using Transform_t = __TL_apply_t(detail::TypeTransformer, IN, F);

namespace detail {
    template<FiniteListConcept IN, __TL_lambda(F, __Set())>
    auto DeductTransform() -> Transform_t<IN, F>;

    template<FiniteListConcept IN, __TL_lambda(F, auto)>
    auto DeductTransform() -> TransformValue_t<IN, F>;

    template<FiniteListConcept IN, auto F>
    auto DeductTransform() -> TransformValueF_t<IN, F>;
}

TYPE_LIST_NS_END

#define __TL_map(IN, F) \
decltype(TYPE_LIST_NS::detail::DeductTransform<IN, F>())

#endif //TYPE_LIST_TRANSFORM_H
