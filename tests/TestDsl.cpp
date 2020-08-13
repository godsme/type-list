//
// Created by godsme on 8/13/20.
//
#include <dsl/Link.h>
#include <dsl/Node.h>
#include <dsl/Graph.h>
#include <type_traits>
#include <catch.hpp>


    struct Node_1 {};
    struct Node_2 {};
    struct Node_3 {};
    struct Node_4 {};
    struct Node_5 {};

    struct Port_1 {};
    struct Port_2 {};
    struct Port_3 {};
    struct Port_4 {};

    struct Pred_1{};

    using link1 = Link<auto (Port_1) -> Exclusive<Pred_1, Node_1, Node_2>>;
    using link2 = Link<auto (Port_2) -> Exclusive<Pred_1, Node_3, Node_2>>;
    using link3 = Link<auto (Port_3) -> Maybe<Pred_1, Node_3>>;
    using link4 = Link<auto (Port_4) -> Node_4>;

    using node1 = Node<Node_5, link1, link2, link3, link4>;

    template<typename T> struct S;

namespace {
    TEST_CASE("nodes") {
        REQUIRE(std::is_same_v<node1::Decendents, __TL_list(Node_1, Node_2, Node_3, Node_4)>);
    }

    S<typename Graph<node1>::AllNodes> s;
}