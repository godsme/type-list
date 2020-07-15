//
// Created by godsme on 7/15/20.
//

#include <type-list/algo/Curry.h>
#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    template<typename T1, typename T2> struct Foo {};

    template<template<typename> typename F>
    struct Bar {
        using type = typename F<double>::type;
    };
    SCENARIO("curry") {
        WHEN("apply a curried template enough parameter") {
            using type = Curry<Foo>::apply<int>::apply<double>::type;
            THEN("should be able to access it parameter") {
                REQUIRE(std::is_same_v<type, Foo<int, double>>);
            }
        }
        WHEN("apply a curried template part of its parameters") {
            using partial = Curry<Foo>::apply<int>;
            THEN("") {
                using type = typename Bar<partial::template apply>::type;
                REQUIRE(std::is_same_v<type, Foo<int, double>>);
            }
        }



    }
}
