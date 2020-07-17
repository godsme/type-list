//
// Created by godsme on 7/16/20.
//

#include <type-list/algo/Bind.h>
#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    template<typename ...>
    struct Foo {};

    template<typename T> struct S;

    SCENARIO("Bind") {
        using Bound = Bind<Foo, _1_, int, _2_, double>;
        WHEN("apply a bound template directly") {
            using type = typename Bound::template apply<char, float>;
            THEN("should put the applied types in correct position") {
                REQUIRE(std::is_same_v<type, Foo<char, int, float, double>>);
            }
        }

        WHEN("pass it to a type list") {
            using type = decltype(TypeList<char, float>::exportTo<__TL_bind(Foo, _1_, int, _2_, double)>());
            REQUIRE(std::is_same_v<type, Foo<char, int, float, double>>);
        }
    }
}