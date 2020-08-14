//
// Created by godsme on 8/13/20.
//
#include <dsl/Link.h>
#include <dsl/Node.h>
#include <dsl/Graph.h>
#include <type-list/types/Map.h>
#include <type_traits>
#include <catch.hpp>

using namespace TYPE_LIST_NS;

struct Node_1 {};
struct Node_2 {};
struct Node_3 {};
struct Node_4 {};
struct Node_5 {};
struct Node_6 {};
struct Node_7 {};
struct Node_8 {};

struct Port_1 {};
struct Port_2 {};
struct Port_3 {};
struct Port_4 {};
struct Port_5 {};
struct Port_6 {};
struct Port_7 {};
struct Port_8 {};

struct Pred_1{};

using graph = __graph(
    __node( Node_1
          , __port(Port_1) -> __exclusive(Pred_1, Node_2, Node_3)
          , __port(Port_2) -> __fork(Node_4, Node_2)
          , __port(Port_3) -> __maybe(Pred_1, Node_5)
          , __port(Port_4) -> Node_6),
    __node( Node_3
          , __port(Port_5) -> __maybe(Pred_1, Node_4)
          , __port(Port_6) -> Node_5),
    __node( Node_4
          , __port(Port_7) -> Node_6
          , __port(Port_8) -> Node_7));

    template<typename T> struct S;

    //S<graph::SortedNodes> s;
namespace {
    TEST_CASE("nodes") {
        REQUIRE(std::is_same_v<__TL_list(Node_1, Node_2, Node_3, Node_5, Node_4, Node_7, Node_6), graph::SortedNodes>);
    }
//    TEST_CASE("nodes") {
//        REQUIRE(std::is_same_v<node5::Decendents, __TL_list(Node_1, Node_2, Node_3, Node_4)>);
//    }
//
//    TEST_CASE("graph") {
//        REQUIRE(std::is_same_v<type::AllNodes,
//                __TL_list(Node_5, Node_6, Node_3, Node_1, Node_2, Node_4, Node_7)>);
//    }

}