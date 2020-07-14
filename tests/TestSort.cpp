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

    __TL_lambda(LesserSize, typename T1, typename T2) __return_v(sizeof(T1) < sizeof(T2));
    SCENARIO("sort an empty list") {
        using type = __TL_sort(__TL_list(), LesserSize);
        REQUIRE(std::is_same_v<__TL_list(), type>);
    }
    SCENARIO("sort an type list") {
        using type = __TL_sort(__TL_list(int, char, long double, short, long, double, bool), LesserSize);
        REQUIRE(std::is_same_v<__TL_list(char, bool, short, int, long, double, long double), type>);
    }

    __TL_lambda(GreaterSize, typename T1, typename T2) __return_v(sizeof(T1) > sizeof(T2));
    SCENARIO("sort an type list with reverse order") {
        using type = __TL_sort(__TL_list(int, char, long double, short, long, double, bool), GreaterSize);
        REQUIRE(std::is_same_v<__TL_list(long double, long, double, int, short, char, bool), type>);
    }
}