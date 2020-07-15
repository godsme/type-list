//
// Created by godsme on 7/15/20.
//

#include <type-list/algo/PipeLine.h>
#include <type-list/algo/Take.h>
#include <type-list/types/List.h>

#include <type_traits>
#include <catch.hpp>


namespace {
    using namespace TYPE_LIST_NS;

    SCENARIO("pipe line") {
        using type = __TL_pipeline(__TL_infinite(1), __TL_Take(3));
        REQUIRE(std::is_same_v<__TL_list(1,2,3), type>);
    }
}