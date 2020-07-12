//
// Created by godsme on 7/12/20.
//

#ifndef TYPE_LIST_EXPORTABLELISTCONCEPT_H
#define TYPE_LIST_EXPORTABLELISTCONCEPT_H

#include <type-list/Signatures.h>
#include <type-list/concept/ListConcept.h>

TYPE_LIST_NS_BEGIN

//namespace details {
//    template<template<typename ...> typename >
//    struct __SeCrEtE_aNd_StUpId_TyPe_LiSt_ReSuLt {};
//}

template<typename T>
concept ExportableListConcept =
        std::is_base_of_v<ExportableTypeListSignature, T>;

TYPE_LIST_NS_END

#endif //TYPE_LIST_EXPORTABLELISTCONCEPT_H
