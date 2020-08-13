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
struct Node_6 {};
struct Node_7 {};

struct Port_1 {};
struct Port_2 {};
struct Port_3 {};
struct Port_4 {};
struct Port_5 {};
struct Port_6 {};
struct Port_7 {};
struct Port_8 {};

struct Pred_1{};

using node1 = Node<Node_1,
  Link<auto (Port_1) -> Exclusive<Pred_1, Node_2, Node_3>>,
  Link<auto (Port_2) -> Exclusive<Pred_1, Node_4, Node_2>>,
  Link<auto (Port_3) -> Maybe<Pred_1, Node_5>>,
  Link<auto (Port_4) -> Node_6>>;

using node3 = Node<Node_3,
    Link<auto (Port_5) -> Maybe<Pred_1, Node_4>>,
    Link<auto (Port_6) -> Node_5>>;

using node5 = Node<Node_4,
        Link<auto (Port_7) -> Node_6>,
        Link<auto (Port_8) -> Node_7>>;

    template<typename T> struct S;

    using type = Graph<node3, node5, node1>;
    S<Graph<node3, node5, node1>::SortedNodes> s;

namespace {
//    TEST_CASE("nodes") {
//        REQUIRE(std::is_same_v<node5::Decendents, __TL_list(Node_1, Node_2, Node_3, Node_4)>);
//    }
//
//    TEST_CASE("graph") {
//        REQUIRE(std::is_same_v<type::AllNodes,
//                __TL_list(Node_5, Node_6, Node_3, Node_1, Node_2, Node_4, Node_7)>);
//    }

}