//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LAMBDA_H
#define TYPE_LIST_LAMBDA_H

#define __Set(...) typename __VA_ARGS__
#define __TL_lambda_t(p, ...) template <p, ##__VA_ARGS__> typename
#define __TL_lambda(name, ...) template <__VA_ARGS__> class name
#define __return_t(...) { public: using type = __VA_ARGS__; }
#define __return_v(...) { public: constexpr static auto value = __VA_ARGS__; }

#define __TL_apply(f, ...) f<__VA_ARGS__>
#define __TL_apply_t(f, ...) typename f<__VA_ARGS__>::type
#define __TL_apply_v(f, ...) f<__VA_ARGS__>::value

#define __TL_append_t(list, ...) typename list::template appendType<__VA_ARGS__>
#define __TL_pattern(name, ...) struct name <__VA_ARGS__>
#endif //TYPE_LIST_LAMBDA_H
