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

    __TL_lambda(NonZero, auto V) __return_v(V != 0);
    SCENARIO("Partition Value List With NonZERO") {
        using type = __TL_partition(NonZero, __TL_list(1, 2, 3));
        REQUIRE(std::is_same_v<__TL_list(1, 2, 3), typename type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(), typename type::rest>);
    }
    __TL_lambda(Greater, auto V) __return_v(V > 1);
    SCENARIO("Partition Value List") {
        using type = __TL_partition(Greater, __TL_list(1, 2, 3));
        REQUIRE(std::is_same_v<__TL_list(2, 3), typename type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(1), typename type::rest>);
    }
    SCENARIO("Partition Empty List") {
        using type = __TL_partition(Greater, __TL_list());
        REQUIRE(std::is_same_v<__TL_list(), type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(), type::rest>);
    }

    __TL_lambda(Int, typename T) __return_v(std::is_same_v<T, int>);
    SCENARIO("Partition TypeList") {
        using type = __TL_partition(Int, __TL_list(int, double, int));
        REQUIRE(std::is_same_v<__TL_list(int, int), typename type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(double), typename type::rest>);
    }
    SCENARIO("Partition Empty List With Type PRED") {
        using type = __TL_partition(Int, __TL_list());
        REQUIRE(std::is_same_v<__TL_list(), type::satisfied>);
        REQUIRE(std::is_same_v<__TL_list(), type::rest>);
    }
}