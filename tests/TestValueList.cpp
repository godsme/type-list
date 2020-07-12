//
// Created by godsme on 7/12/20.
//

#include <type-list/base/ValueList.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/FiniteListConcept.h>
#include <type-list/concept/InfiniteListConcept.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    template<typename T>
    constexpr bool hasHead = false;

    template<typename T> requires requires { T::Head; }
    constexpr bool hasHead<T> = true;

    template<typename T>
    constexpr bool hasTail = false;

    template<typename T> requires requires { typename T::Tail; }
    constexpr bool hasTail<T> = true;

    template<int ... Ts>
    struct Result {
        enum {
            Num_Of_Ts = sizeof...(Ts)
        };
    };

    SCENARIO("Empty ValueList") {
        using type = ValueList<>;
        THEN("its size should be 0") {
            REQUIRE(type::size == 0);
        }
        THEN("it does not have a head") {
            REQUIRE(!hasHead<type>);
        }
        THEN("it does not have a Tail") {
            REQUIRE(!hasTail<type>);
        }
        THEN("it satisfied ValueListConcept") {
            REQUIRE(ValueListConcept<type>);
        }
        THEN("it satisfied FiniteListConcept") {
            REQUIRE(FiniteListConcept<type>);
        }
        THEN("it's not a InfiniteListConcept") {
            REQUIRE(!InfiniteListConcept<type>);
        }
        THEN("it satisfies ExportableListConcept") {
            REQUIRE(ExportableListConcept<type>);
        }
        THEN("it can be export to a template") {
            REQUIRE(0 == type::exportTo<Result>::Num_Of_Ts);
        }
    }

    SCENARIO("NonEmpty ValueList") {
        using type = ValueList<1,2,3>;
        THEN("its size should be 3") {
            REQUIRE(type::size == 3);
        }
        THEN("it has a head") {
            REQUIRE(hasHead<type>);
        }
        THEN("it has a tail") {
            REQUIRE(hasTail<type>);
        }
        THEN("its tail has a Head") {
            REQUIRE(hasTail<type::Tail>);
        }
        THEN("its tail has a tail") {
            REQUIRE(hasTail<type::Tail>);
        }
        THEN("its head is 1") {
            REQUIRE(type::Head == 1);
        }
        THEN("the 2nd elem is 2") {
            REQUIRE(type::Tail::Head == 2);
        }
        THEN("the 3rd elem is 3") {
            REQUIRE(type::Tail::Tail::Head == 3);
        }
        THEN("it satisfied ValueListConcept") {
            REQUIRE(ValueListConcept<type>);
        }
        THEN("it satisfied FiniteListConcept") {
            REQUIRE(FiniteListConcept<type>);
        }
        THEN("it's not a InfiniteListConcept") {
            REQUIRE(!InfiniteListConcept<type>);
        }
        THEN("it satisfies ExportableListConcept") {
            REQUIRE(ExportableListConcept<type>);
        }
        THEN("it can be export to a template") {
            REQUIRE(3 == type::exportTo<Result>::Num_Of_Ts);
        }
    }
}