//
// Created by godsme on 7/12/20.
//


#include <type-list/types/TypeList.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

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

    template <typename ... Ts>
    struct Result {
        enum { Num_Of_Ts = sizeof...(Ts) };
    };

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
            THEN("it should satisfy ExportableListConcept") {
                REQUIRE(ExportableListConcept<type>);
            }
            THEN("it should satisfy ListConcept") {
                REQUIRE(ListConcept<type>);
            }
            WHEN("export to a template") {
                using result = type::template exportTo<Result>;
                THEN("the num_of_Ts should be 0") {
                    REQUIRE(0 == result::Num_Of_Ts);
                }
            }

            WHEN("append a type") {
                using type1 = type::append<int>;
                THEN("size is 1") {
                    REQUIRE(type1::size == 1);
                }
                THEN("it has a head") {
                    REQUIRE(hasHead<type1>);

                    THEN("its head is appened type") {
                        REQUIRE(std::is_same_v<int, type1::Head>);
                    }
                }
                THEN("it has a tail") {
                    REQUIRE(hasTail<type1>);
                    THEN("its tail does not have a tail") {
                        REQUIRE(!hasTail<type1::Tail>);
                    }
                }
            }

            WHEN("append 2 types") {
                using type1 = type::append<float, double>;
                THEN("size is 2") {
                    REQUIRE(type1::size == 2);
                }
                THEN("it has a head") {
                    REQUIRE(hasHead<type1>);

                    THEN("its head is the 1st appened type") {
                        REQUIRE(std::is_same_v<float, type1::Head>);
                        THEN("it has a tail") {
                            REQUIRE(hasTail<type1>);
                            THEN("the head of its tail is double") {
                                REQUIRE(std::is_same_v<double, type1::Tail::Head>);
                            }

                        }
                    }
                }
            }

            WHEN("append another TypeList") {
                using type1 = type::appendList<TypeList<int, double>>;
                THEN("size is 2") {
                    REQUIRE(type1::size == 2);
                    THEN("it has a head") {
                        REQUIRE(hasHead<type1>);

                        THEN("its head is the 1st appened type") {
                            REQUIRE(std::is_same_v<int, type1::Head>);
                            THEN("it has a tail") {
                                REQUIRE(hasTail<type1>);
                                THEN("the head of its tail is double") {
                                    REQUIRE(std::is_same_v<double, type1::Tail::Head>);
                                }

                            }
                        }
                    }
                }
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
            WHEN("append another typelist") {
                using type1 = type::appendList<TypeList<float, char>>;
                THEN("it has 5 types") {
                    REQUIRE(type1::size == 5);
                }
                THEN("its 4th type is float") {
                    REQUIRE(std::is_same_v<float, type1::Tail::Tail::Tail::Head>);
                }
            }
            WHEN("prepend another typelist") {
                using type1 = type::prependList<TypeList<float, char>>;
                THEN("it has 5 types") {
                    REQUIRE(type1::size == 5);
                }
                THEN("its 1st type is float") {
                    REQUIRE(std::is_same_v<float, type1::Head>);
                }
                THEN("its 4th type is double") {
                    REQUIRE(std::is_same_v<double, type1::Tail::Tail::Tail::Head>);
                }
            }
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
                REQUIRE(std::is_base_of_v<detail::TypeListSignature, type>);
            }
            WHEN("export to a template") {
                using result = decltype(type::template exportTo<Result>());
                THEN("the num_of_Ts should be 3") {
                    REQUIRE(3 == result::Num_Of_Ts);
                }
            }
            WHEN("export it's tail to a template") {
                using result = decltype(type::Tail::template exportTo<Result>());
                THEN("the num_of_Ts should be 2") {
                    REQUIRE(2 == result::Num_Of_Ts);
                }
            }
            THEN("it should satisfy ExportableListConcept") {
                REQUIRE(ExportableListConcept<type>);
            }
            THEN("it should satisfy ListConcept") {
                REQUIRE(ListConcept<type>);
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