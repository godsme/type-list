//
// Created by godsme on 7/13/20.
//

#include <type-list/types/List.h>

#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    SCENARIO("infinite int list") {
        using type = InfiniteIntList<0, 2>;
        REQUIRE(type::Head == 0);
        REQUIRE(type::Tail::Head == 2);
        REQUIRE(type::Tail::Tail::Head == 4);
    }
}