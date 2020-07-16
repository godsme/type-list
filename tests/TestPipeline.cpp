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

    constexpr auto Greater = [](auto lhs, auto rhs) -> bool { return lhs > rhs; };
    SCENARIO("pipe line") {
        using type = __TL_pipeline(__TL_infinite(1), __TL_Take(3), __TL_Sort(Greater));
        REQUIRE(std::is_same_v<__TL_list(3,2,1), type>);
    }
}