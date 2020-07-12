//
// Created by godsme on 7/12/20.
//

#include <catch.hpp>
#include <type-list/TypeList.h>

namespace {
    using namespace TYPE_LIST_NS;
    TEST_CASE("TypeList") {
        SECTION("the size of an empty TypeList should be 0") {
            REQUIRE(TypeList<>::size == 0);
        }
        WHEN("TypeList is initialized with 3 types") {
            THEN("it's size should be 3") {
                REQUIRE(TypeList<int, double, long>::size == 3);
            }
        }
        WHEN("TypeList is initialized with 5 types") {
            THEN("it's size should be 5") {
                REQUIRE(TypeList<int, char, int, double, long>::size == 5);
            }
        }

    }
}