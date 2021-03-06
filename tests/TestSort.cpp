//
// Created by godsme on 7/14/20.
//

#include <type-list/algo/Sort.h>
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

    template<typename T> struct S;

    __TL_lambda(LesserSize, typename T1, typename T2) __return_v(sizeof(T1) < sizeof(T2));
    SCENARIO("sort an empty list") {
        using type = __TL_Sort(LesserSize, __TL_list());
        REQUIRE(std::is_same_v<__TL_list(), type>);
    }
    SCENARIO("sort an type list") {
        using type = __TL_Sort(LesserSize, __TL_list(int, char, long double, short, long, double, bool));
        //REQUIRE(std::is_same_v<__TL_list(char, bool, short, int, long, double, long double), type>);
    }

    __TL_lambda(GreaterSize, typename T1, typename T2) __return_v(sizeof(T1) > sizeof(T2));
    SCENARIO("sort an type list with reverse order") {
        using type = __TL_Sort(GreaterSize, __TL_list(int, char, long double, short, long, double, bool));
        REQUIRE(std::is_same_v<__TL_list(long double, long, double, int, short, char, bool), type>);
    }

    __TL_lambda(LesserValue, int V1, int V2) __return_v(V1 < V2);
    SCENARIO("sort a value list") {
        using type = __TL_Sort(LesserValue, __TL_list(18, 93, 2, 41, 1));
        REQUIRE(std::is_same_v<__TL_list(1, 2, 18, 41, 93), type>);
    }

    __TL_lambda(GreaterValue, int V1, int V2) __return_v(V1 > V2);
    SCENARIO("sort a value list in greater way") {
        using type = __TL_Sort(GreaterValue, __TL_list(18, 93, 2, 41, 1));
        REQUIRE(std::is_same_v<__TL_list(93, 41, 18, 2, 1), type>);
    }

    constexpr auto GreaterValueF(int V1, int V2) -> bool { return V1 > V2; }
    SCENARIO("sort a value list in function") {
        using type = __TL_Sort(GreaterValueF, __TL_list(18, 93, 2, 41, 1));
        REQUIRE(std::is_same_v<__TL_list(93, 41, 18, 2, 1), type>);
    }

    constexpr auto LesserValueF = [](int V1, int V2) { return V1 < V2; };
    SCENARIO("sort a value list in a lambda") {
        using type = __TL_Sort(LesserValueF, __TL_list(18, 93, 2, 41, 1));
        REQUIRE(std::is_same_v<__TL_list(1, 2, 18, 41, 93), type>);
    }
}