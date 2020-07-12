//
// Created by godsme on 7/12/20.
//

#include <catch.hpp>
#include <type-list/TypeList.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type_traits>

namespace {
    using namespace TYPE_LIST_NS;

    template <typename T>
    constexpr bool hasHead = false;

    template<typename T> requires requires { typename T::Head; }
    constexpr bool hasHead<T> = true;

    template <typename T>
    constexpr bool hasTail = false;

    template<typename T> requires requires { typename T::Tail; }
    constexpr bool hasTail<T> = true;

    TEST_CASE("TypeList") {
        GIVEN("an empty TypeList") {
            using type = TypeList<>;
            THEN("its size should be 0") {
                REQUIRE(type::size == 0);
            }
            THEN("it does not satisfy NonEmptyListConcept") {
                REQUIRE(!NonEmptyListConcept<type>);
            }
            THEN("it does not have a head") {
                REQUIRE(!hasHead<type>);
            }
            THEN("it does not have a Tail") {
                REQUIRE(!hasTail<type>);
            }
            THEN("it should has a TypeListSignature") {
                REQUIRE(std::is_base_of_v<TypeListSignature, type>);
            }

        }

        WHEN("TypeList is initialized with 3 types") {
            THEN("it's size should be 3") {
                REQUIRE(TypeList<int, double, long>::size == 3);
            }
        }
        WHEN("TypeList is initialized with 5 types") {
            THEN("it's size should be 5") {
                REQUIRE(TypeList<int, char, int, double, long>::size == 5);
            }
        }
        GIVEN("a TypeList initialized with 3 types") {
            using type = TypeList<char, double, long>;
            THEN("its head should be char") {
                REQUIRE(std::is_same_v<char, typename type::Head>);
            }
            THEN("the head of its tail should be double") {
                REQUIRE(std::is_same_v<double, typename type::Tail::Head>);
            }
            THEN("the head of its tail's tail should be long") {
                REQUIRE(std::is_same_v<long, typename type::Tail::Tail::Head>);
            }
            THEN("it should has a TypeListSignature") {
                REQUIRE(std::is_base_of_v<TypeListSignature, type>);
            }
            THEN("it has a Tail") {
                REQUIRE(hasTail<type>);
                THEN("its tail also has a Tail") {
                    REQUIRE(hasTail<type::Tail>);
                    THEN("the tail of its tail also has a Tail") {
                        REQUIRE(hasTail<type::Tail::Tail>);
                        THEN("the tail of tail of its tail does not have a Tail") {
                            REQUIRE(!hasTail<type::Tail::Tail::Tail>);
                        }
                    }
                }
            }
            THEN("it satisfy NonEmptyListConcept") {
                REQUIRE(NonEmptyListConcept<type>);
                THEN("its tail also satisfy") {
                    REQUIRE(NonEmptyListConcept<type::Tail>);
                    THEN("the tail of its tail also satisfy") {
                        REQUIRE(NonEmptyListConcept<type::Tail::Tail>);
                        THEN("the tail of tail of its tail does not satisfy") {
                            REQUIRE(!NonEmptyListConcept<type::Tail::Tail::Tail>);
                        }
                    }
                }
            }
            THEN("it has a Head") {
                REQUIRE(hasHead<type>);
                THEN("its tail also has a Head") {
                    REQUIRE(hasHead<typename type::Tail>);
                    THEN("the tail of its tail also has a Head") {
                        REQUIRE(hasHead<typename type::Tail::Tail>);
                        THEN("the tail of tail of its tail does not have a HEAD") {
                            REQUIRE(!hasHead<typename type::Tail::Tail::Tail>);
                        }
                    }
                }
            }
        }

    }
}