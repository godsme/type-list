//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_SIGNATURES_H
#define TYPE_LIST_SIGNATURES_H

#include <type-list/type-list-ns.h>

TYPE_LIST_NS_BEGIN

struct ListSignature {};
struct TypeListSignature : ListSignature {};
struct ExportableListSignature {};
struct InfiniteListSignature {};
struct ValueListSignature : ListSignature {};
struct AppendableTypeList {};

TYPE_LIST_NS_END

#endif //TYPE_LIST_SIGNATURES_H
