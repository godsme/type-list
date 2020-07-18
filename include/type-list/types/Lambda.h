//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LAMBDA_H
#define TYPE_LIST_LAMBDA_H

#define __Set(...) typename __VA_ARGS__
#define __TL_lambda_t(p, ...) template <p, ##__VA_ARGS__> typename
#define __TL_lambda(name, ...) template <__VA_ARGS__> class name
#define __result_t(...) public: using type = __VA_ARGS__
#define __return_t(...) { __result_t(__VA_ARGS__); }
#define __result_v(...) public: constexpr static auto value = __VA_ARGS__
#define __return_v(...) { __result_v(__VA_ARGS__); }

#define __TL_apply(f, ...) f<__VA_ARGS__>
#define __TL_apply_t(f, ...) typename f<__VA_ARGS__>::type
#define __TL_apply_v(f, ...) f<__VA_ARGS__>::value

#define __TL_call(callable, ...) typename callable::template apply<__VA_ARGS__>
#define __return_callable(p, ...) { public : template <p> using apply = __VA_ARGS__; }

#define __TL_params(...) <__VA_ARGS__>
#define __return_lambda_t(params, ...) { public: template params using apply = __VA_ARGS__; }
#define __return_apply_t(...) __return_t(__TL_apply_t(__VA_ARGS__))
#define __return_apply_v(...) __return_v(__TL_apply_v(__VA_ARGS__))

#define __scope_lambda(scope, f) scope::template f
#define __TL_scope_apply(scope, f, ...) typename __scope_lambda(scope, f)<__VA_ARGS__>
#define __scope_apply_t(scope, f, ...) __scope_apply(scope, f, __VA_ARGS__)::type
#define __TL_append_t(list, ...) typename list::template appendType<__VA_ARGS__>
#define __TL_pattern(name, ...) struct name <__VA_ARGS__>
#endif //TYPE_LIST_LAMBDA_H
