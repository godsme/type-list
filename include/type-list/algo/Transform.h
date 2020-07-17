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
#include <type-list/types/List.h>

TYPE_LIST_NS_BEGIN

namespace detail {
    __TL_lambda(Transform
            , typename IN
            , __TL_lambda_t(typename)
            , typename OUT = EmptyList)
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
    template<typename F, auto V>
    concept V2VConcept = requires {
        F::template apply<V>::value;
    };

    template<typename F, auto V>
    concept V2TConcept = requires {
        typename F::template apply<V>::type;
    };

    template<typename F, typename T>
    concept T2VConcept = TypeTemplateConcept<F> && requires {
        F::template apply<T>::value;
    };

    template<typename F, typename T>
    concept T2TConcept = TypeTemplateConcept<F> && requires {
        typename F::template apply<T>::type;
    };
}

namespace detail {
    template<typename F, typename IN> struct TypeTransformer;

    template<ValueTemplateConcept F, NonEmptyFiniteValueListConcept IN>
    requires V2VConcept<F, IN::Head>
    class TypeTransformer<F, IN> {
        __TL_lambda(Mapper, __Set(T))
        __return_t(Value<__TL_apply_v(F::template apply, T::value)>);
    public:
        using type = __TL_apply_t(Transform,
                                  List<IN>,
                                  Mapper);
    };

    template<ValueTemplateConcept F, NonEmptyFiniteValueListConcept IN>
    requires V2TConcept<F, IN::Head>
    class TypeTransformer<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_apply_t(F::template apply, T::value);
    public:
        using type = __TL_apply_t(Transform, List<IN>, Mapper);
    };

    template<ValueConcept F, NonEmptyFiniteValueListConcept IN>
    class TypeTransformer<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_t(Value<F::value(T::value)>);
    public:
        using type = __TL_apply_t(detail::Transform, List<IN>, Mapper);
    };

    template<TypeTemplateConcept F, NonEmptyFiniteTypeListConcept IN>
    requires T2VConcept<F, typename IN::Head>
    class TypeTransformer<F, IN> {
        __TL_lambda(Mapper, __Set(T)) __return_t(Value<F::template apply<T>::value>);
    public:
        using type = __TL_apply_t(Transform, IN, Mapper);
    };

    template<TypeTemplateConcept F, NonEmptyFiniteTypeListConcept IN>
    requires T2TConcept<F, typename IN::Head>
    struct TypeTransformer<F, IN>
        __return_apply_t(detail::Transform, IN, F::template apply);

    template<typename F, EmptyFiniteListConcept IN>
    struct TypeTransformer<F, IN> __return_t(EmptyList);
}

template<typename F, typename IN>
using Transform_t = __TL_apply_t(detail::TypeTransformer, F, IN);

//namespace detail {
//    template<FiniteListConcept IN, __TL_lambda(F, __Set())>
//    auto DeductTransform() -> Transform_t<TypeTemplate<F>, IN>;
//
//    template<FiniteListConcept IN, __TL_lambda(F, auto)>
//    auto DeductTransform() -> Transform_t<ValueTemplate<F>, IN>;
//
//    template<FiniteListConcept IN, auto F>
//    auto DeductTransform() -> Transform_t<Value<F>, IN>;
//}

TYPE_LIST_NS_END

#define __TL_Map(F, ...) \
TYPE_LIST_NS::Transform_t<__TL_toType(F), __VA_ARGS__>

#endif //TYPE_LIST_TRANSFORM_H
