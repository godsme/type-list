//
// Created by godsme on 7/13/20.
//

#ifndef TYPE_LIST_LAMBDA_H
#define TYPE_LIST_LAMBDA_H

#define __TL_Set(t) typename T
#define __TL_lambda(name, ...) template <__VA_ARGS__> class name
#define __return_t(...) { public: using type = __VA_ARGS__; }
#define __return_v(...) { public: constexpr static auto value = __VA_ARGS__; }

#endif //TYPE_LIST_LAMBDA_H
