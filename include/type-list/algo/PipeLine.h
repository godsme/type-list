//
// Created by godsme on 7/15/20.
//

#ifndef TYPE_LIST_PIPELINE_H
#define TYPE_LIST_PIPELINE_H

#include <type-list/type-list-ns.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/Lambda.h>
#include <type-list/types/List.h>
#include <type-list/concept/TypeListConcept.h>

TYPE_LIST_NS_BEGIN

/////////////////////////////////////////////////////////////////////////////////////////
template<typename IN, typename ... OPs>
class PipeLine final {
    __TL_lambda(TypeListTrait, typename T) __return_t(TypeList<T>);
    __TL_lambda(TypeListTrait, TypeListConcept T)
    <T> __return_t(T);

    template<typename OP>
    struct ListOperation {

        template<typename COMPOSED_OP>
        struct Compose {
            template<typename INPUT>
            struct Result {
                using output = typename TypeListTrait<typename OP::template type<INPUT>>::type;
                using type = typename COMPOSED_OP::template Result<output>::type;
            };
        };

        template<typename INPUT>
        struct Result {
            using type = typename OP::template type<INPUT>;
        };
    };

    //////////////////////////////////////////////////////////////////////////
    __TL_lambda(ComposeAll, typename ... Ts);
    __TL_lambda(ComposeAll, typename H, typename ... Ts)
    <H, Ts...> __return_t(
            __TL_apply(typename ListOperation<H>::template Compose,
                    __TL_apply_t(ComposeAll, Ts...)));

    __TL_lambda(ComposeAll, typename H)
    <H> __return_t(ListOperation<H>);

    using result = __TL_apply_t(ComposeAll, OPs...);
public:
    using type = __TL_apply_t(result::template Result, IN);
};

TYPE_LIST_NS_END

#define __TL_pipeline(list, ...) \
__TL_apply_t(TYPE_LIST_NS::PipeLine, list, __VA_ARGS__)

#endif //TYPE_LIST_PIPELINE_H