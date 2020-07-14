//
// Created by godsme on 7/13/20.
//

#include <type-list/algo/Drop.h>
#include <type-list/types/List.h>

#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    SCENARIO("drop an empty list") {
        WHEN("drop 0 elem from a type list") {
            using type = __TL_drop(TypeList<>, 0);
            THEN("should return empty type list") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }

        WHEN("drop 0 elem from value list") {
            using type = __TL_drop(ValueList<>, 0);
            THEN("should return an empty type list") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }

        WHEN("drop 0 elem from empty list") {
            using type = __TL_drop(__TL_list(), 0);
            THEN("should return an empty list") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }
    }

    SCENARIO("drop an type-list") {
        using list = TypeList<int, double>;
        WHEN("drop 0 elem") {
            using type = __TL_drop(list, 0);
            THEN("should return original type list") {
                REQUIRE(std::is_same_v<type, TypeList<int, double>>);
            }
        }
        WHEN("drop 1 elem") {
            using type = __TL_drop(list, 1);
            THEN("should get a TypeList with the 1st elem dropped") {
                REQUIRE(std::is_same_v<type, TypeList<double>>);
            }
        }

        WHEN("drop 2 elem") {
            using type = __TL_drop(list, 2);
            THEN("should get a TypeList with the 2 elems dropped") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }
    }

    SCENARIO("drop an value-list") {
        using list = ValueList<0, 1>;
        WHEN("drop 0 elem") {
            using type = __TL_drop(list, 0);
            THEN("should return original list") {
                REQUIRE(std::is_same_v<type, ValueList<0, 1>>);
            }
        }
        WHEN("drop 1 elem") {
            using type = __TL_drop(list, 1);
            THEN("should get a list with the 1st elem dropped") {
                REQUIRE(std::is_same_v<type, ValueList<1>>);
            }
        }

        WHEN("drop 2 elem") {
            using type = __TL_drop(list, 2);
            THEN("should get a list with the 2 elems dropped") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }
    }

    SCENARIO("drop an infnite value-list") {
        using list = InfiniteIntList<1, 2>;
        WHEN("drop 0 elem") {
            using type = __TL_drop(list, 0);
            THEN("the head should be the initial value") {
                REQUIRE(type::Head == 1);
            }
        }
        WHEN("drop 1 elem") {
            using type = __TL_drop(list, 1);
            THEN("should get a list with the 1st elem dropped") {
                REQUIRE(type::Head == 3);
            }
        }

        WHEN("drop 2 elem") {
            using type = __TL_drop(list, 2);
            THEN("should get a list with the 2 elems dropped") {
                REQUIRE(type::Head == 5);
            }
        }
    }
}