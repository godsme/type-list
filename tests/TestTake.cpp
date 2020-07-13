//
// Created by godsme on 7/13/20.
//

#include <type-list/algo/Take.h>
#include <type-list/types/List.h>

#include <type_traits>
#include <catch.hpp>


namespace {
    using namespace TYPE_LIST_NS;

    SCENARIO("take an empty list") {
        WHEN("take 0 elem from a type list") {
            using type = __TL_take(TypeList<>, 0);
            THEN("should return empty type list") {
                REQUIRE(std::is_same_v<type, TypeList<>>);
            }
        }

        WHEN("take 0 elem from value list") {
            using type = __TL_take(ValueList<>, 0);
            THEN("should return an empty type list") {
                REQUIRE(std::is_same_v<type, ValueList<>>);
            }
        }

        WHEN("take 0 elem from empty list") {
            using type = __TL_take(__TL_list(), 0);
            THEN("should return an empty list") {
                REQUIRE(std::is_same_v<type, __TL_list()>);
            }
        }
    }

    SCENARIO("take an type-list") {
        using list = TypeList<int, double>;
        WHEN("take 0 elem") {
            using type = __TL_take(list, 0);
            THEN("should return an empty type list") {
                REQUIRE(std::is_same_v<type, TypeList<>>);
            }
        }
        WHEN("take 1 elem") {
            using type = __TL_take(list, 1);
            THEN("should get a TypeList with the 1st elem") {
                REQUIRE(std::is_same_v<type, TypeList<int>>);
            }
        }

        WHEN("take 2 elems") {
            using type = __TL_take(list, 2);
            THEN("should get a TypeList with the 2 elems taken") {
                REQUIRE(std::is_same_v<type, TypeList<int, double>>);
            }
        }
    }

    SCENARIO("take an value-list") {
        using list = ValueList<1, 2>;
        WHEN("drop 0 elem") {
            using type = __TL_take(list, 0);
            THEN("should return an empty list") {
                REQUIRE(std::is_same_v<type, ValueList<>>);
            }
        }
        WHEN("take 1 elem") {
            using type = __TL_take(list, 1);
            THEN("should get a list with the 1st elem taken") {
                REQUIRE(std::is_same_v<type, ValueList<1>>);
            }
        }

        WHEN("take 2 elem") {
            using type = __TL_take(list, 2);
            THEN("should get a TypeList with the 2 elems dropped") {
                REQUIRE(std::is_same_v<type, ValueList<1, 2>>);
            }
        }
    }

    SCENARIO("take from an infnite value-list") {
        using list = __TL_infinite(1, 2);
        WHEN("drop 0 elem") {
            using type = __TL_take(list, 0);
            THEN("should return an empty list") {
                REQUIRE(std::is_same_v<type, ValueList<>>);
            }
        }
        WHEN("take 1 elem") {
            using type = __TL_take(list, 1);
            THEN("should get a list with the 1st elem taken") {
                REQUIRE(std::is_same_v<type, ValueList<1>>);
            }
        }

        WHEN("take 2 elems") {
            using type = __TL_take(list, 2);
            THEN("should get a list with the 2 elems taken") {
                REQUIRE(std::is_same_v<type, ValueList<1, 3>>);
            }
        }

        WHEN("take 3 elems") {
            using type = __TL_take(list, 3);
            THEN("should get a list with the 2 elems taken") {
                REQUIRE(std::is_same_v<type, ValueList<1, 3, 5>>);
            }
        }
    }

    SCENARIO("take from an infnite type-list") {
        using list = __TL_repeat(int);
        WHEN("drop 0 elem") {
            using type = __TL_take(list, 0);
            THEN("should return an empty list") {
                REQUIRE(std::is_same_v<type, TypeList<>>);
            }
        }
        WHEN("take 1 elem") {
            using type = __TL_take(list, 1);
            THEN("should get a list with the 1st elem taken") {
                REQUIRE(std::is_same_v<type, TypeList<int>>);
            }
        }

        WHEN("take 2 elems") {
            using type = __TL_take(list, 2);
            THEN("should get a list with the 2 elems taken") {
                REQUIRE(std::is_same_v<type, TypeList<int, int>>);
            }
        }

        WHEN("take 3 elems") {
            using type = __TL_take(list, 3);
            THEN("should get a list with the 2 elems taken") {
                REQUIRE(std::is_same_v<type, TypeList<int, int, int>>);
            }
        }
    }
}