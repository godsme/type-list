//
// Created by godsme on 7/19/20.
//

#include <type-list/algo/Fold.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

#define ASSERT_EQ_T(a, b) REQUIRE(std::is_same_v<a, b>)

    __TL_lambda(Add, size_t ACC, typename T)
    __return_v(ACC + sizeof(T));

    SCENARIO("foldl an empty list with Raw FOLD_L") {
        using list = List<__TL_list(0)>;
        using type = typename detail::FoldL<__TL_toType(Add)::template apply, typename list::Head, typename list::Tail>::type;
        //using type = __TL_FoldL(__TL_list(), Add, 0);
        REQUIRE(type::value == 0);
    }

    SCENARIO("foldl an empty list with Raw FOLD_Type") {
        using list = List<__TL_list(0)>;
        using type = detail::FoldType<true, __TL_toType(Add), list>;
        //using type = __TL_FoldL(__TL_list(), Add, 0);
        REQUIRE(type::type::value == 0);
    }

    SCENARIO("foldl an empty list with FoldL") {
        using type = __TL_FoldL(__TL_list(), Add, 0);
        REQUIRE(type::value == 0);
    }

    SCENARIO("foldl a non-empty list with FoldL") {
        using type = __TL_FoldL(__TL_list(1,2,3), Add, 0);
        REQUIRE(type::value == 6);
    }
}