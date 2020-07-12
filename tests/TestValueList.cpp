//
// Created by godsme on 7/12/20.
//


#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/FiniteListConcept.h>
#include <type-list/concept/InfiniteListConcept.h>
#include <type-list/base/ValueList.h>
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

    SCENARIO("Empty ValueList append") {
        using type = ValueList<>::append<1,2,3>;
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
    }

    SCENARIO("Empty ValueList append another") {
        using type = ValueList<>::appendList<ValueList<1,2,3>>;
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
    }

    SCENARIO("Empty ValueList prepend another") {
        using type = ValueList<>::prependList<ValueList<1,2,3>>;
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
    }

    SCENARIO("Empty ValueList prepend") {
        using type = ValueList<>::prepend<1,2,3>;
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
    SCENARIO("NonEmpty ValueList append") {
        using type = ValueList<1, 2, 3>::append<4,5>;
        THEN("its size should be 5") {
            REQUIRE(type::size == 5);
        }
        THEN("its 3rd elem should be 3") {
            REQUIRE(type::Tail::Tail::Head == 3);
        }
        THEN("its 4th elem should be 4") {
            REQUIRE(type::Tail::Tail::Tail::Head == 4);
        }
        THEN("its 5th elem should be 5") {
            REQUIRE(type::Tail::Tail::Tail::Tail::Head == 5);
        }
    }

    SCENARIO("NonEmpty ValueList append another") {
        using type1 = ValueList<1, 2, 3>::appendList<ValueList<4, 5>>;
        using type = ValueList<1, 2, 3>::appendList<ValueList<4,5>>;
        THEN("its size should be 5") {
            REQUIRE(type::size == 5);
        }
        THEN("its 3rd elem should be 3") {
            REQUIRE(type::Tail::Tail::Head == 3);
        }
        THEN("its 4th elem should be 4") {
            REQUIRE(type::Tail::Tail::Tail::Head == 4);
        }
        THEN("its 5th elem should be 5") {
            REQUIRE(type::Tail::Tail::Tail::Tail::Head == 5);
        }
    }

    SCENARIO("NonEmpty ValueList prepend") {
        using type = ValueList<1, 2, 3>::prepend<4,5>;
        THEN("its size should be 5") {
            REQUIRE(type::size == 5);
        }
        THEN("its 3rd elem should be 3") {
            REQUIRE(type::Tail::Tail::Head == 1);
        }
        THEN("its 4th elem should be 2") {
            REQUIRE(type::Tail::Tail::Tail::Head == 2);
        }
        THEN("its 5th elem should be 3") {
            REQUIRE(type::Tail::Tail::Tail::Tail::Head == 3);
        }
    }

    SCENARIO("NonEmpty ValueList prepend another") {
        using type = ValueList<1, 2, 3>::prependList<ValueList<4,5>>;
        THEN("its size should be 5") {
            REQUIRE(type::size == 5);
        }
        THEN("its 3rd elem should be 3") {
            REQUIRE(type::Tail::Tail::Head == 1);
        }
        THEN("its 4th elem should be 2") {
            REQUIRE(type::Tail::Tail::Tail::Head == 2);
        }
        THEN("its 5th elem should be 3") {
            REQUIRE(type::Tail::Tail::Tail::Tail::Head == 3);
        }
    }
}