//
// Created by godsme on 7/14/20.
//

#include <type-list/algo/Filter.h>
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

    __TL_lambda(Greater, auto V) __return_v(V > 1);
    SCENARIO("Filter Value List") {
        using type = __TL_filter(__TL_list(1, 2, 3), Greater);
        REQUIRE(std::is_same_v<ValueList<2, 3>, typename type::satisfied>);
        REQUIRE(std::is_same_v<ValueList<1>, typename type::rest>);
    }
    SCENARIO("Filter Empty List") {
        using type = __TL_filter(__TL_list(), Greater);
        REQUIRE(std::is_same_v<__TL_list(), type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(), type::rest>);
    }

    __TL_lambda(Int, typename T) __return_v(std::is_same_v<T, int>);
    SCENARIO("Filter TypeList") {
        using type = __TL_filter(__TL_list(int, double, int), Int);
        REQUIRE(std::is_same_v<__TL_list(int, int), typename type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(double), typename type::rest>);
    }
}