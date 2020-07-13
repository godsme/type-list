//
// Created by godsme on 7/13/20.
//

#include <type-list/types/List.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    SCENARIO("infinite int list") {
        using type = __TL_infinite(0, 2);
        REQUIRE(type::Head == 0);
        REQUIRE(type::Tail::Head == 2);
        REQUIRE(type::Tail::Tail::Head == 4);
    }

    SCENARIO("repeat value list") {
        using type = __TL_repeat(100);
        REQUIRE(type::Head == 100);
        REQUIRE(type::Tail::Head == 100);
        REQUIRE(type::Tail::Tail::Head == 100);
    }

    SCENARIO("repeat a value limited times") {
        using type = __TL_repeat(100, 2);
        REQUIRE(type::Head == 100);
        REQUIRE(type::Tail::Head == 100);
        REQUIRE(EmptyListConcept<type::Tail::Tail>);
    }

    SCENARIO("repeat type list") {
        using type = __TL_repeat(int);
        REQUIRE(std::is_same_v<int, typename type::Head>);
        REQUIRE(std::is_same_v<int, typename type::Tail::Head>);
        REQUIRE(std::is_same_v<int, typename type::Tail::Tail::Head>);
    }
}