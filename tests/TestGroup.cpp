//
// Created by godsme on 7/17/20.
//

#include <type-list/algo/Group.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/List.h>
#include <type-list/types/Lambda.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;



    __TL_lambda(Eq, auto V1, auto V2) __return_v(V1 == V2);

    SCENARIO("Group Value List") {
        using type = __TL_Group(Eq, __TL_list(1, 2, 3, 2, 1, 1, 3));
        using group1 = __TL_list(1,1,1);
        using group2 = __TL_list(2,2);
        using group3 = __TL_list(3,3);
        using result = __TL_list( group1, group2, group3);
        REQUIRE(std::is_same_v<type, result>);
    }

    SCENARIO("Group Value List by lambda") {
        constexpr auto eq = [] (auto lhs, auto rhs) { return lhs == rhs; };
        using type = __TL_Group(eq, __TL_list(1, 2, 3, 2, 1, 1, 3));
        using group1 = __TL_list(1,1,1);
        using group2 = __TL_list(2,2);
        using group3 = __TL_list(3,3);
        using result = __TL_list( group1, group2, group3);
        REQUIRE(std::is_same_v<type, result>);
    }

    template<typename T1, typename T2>
    struct TypeEq {
        constexpr static bool value = std::is_same_v<T1, T2>;
    };

    SCENARIO("Group Type List ") {
        using type = __TL_Group(TypeEq, __TL_list(int, char, double, char, int, int, double));
        using group1 = __TL_list(int,int,int);
        using group2 = __TL_list(char,char);
        using group3 = __TL_list(double,double);
        using result = __TL_list( group1, group2, group3);
        REQUIRE(std::is_same_v<type, result>);
    }

    SCENARIO("group empty list") {
        REQUIRE(std::is_same_v<__TL_list(), __TL_Group(TypeEq, __TL_list())>);
    }
}