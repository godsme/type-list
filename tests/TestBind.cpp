//
// Created by godsme on 7/16/20.
//

#include <type-list/algo/Bind.h>
#include <type_traits>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    template<typename ... Ts>
    struct Foo {};

    template<typename T> struct S;
    SCENARIO("ComposeArgs") {

        WHEN("compose the 0 parameter") {
            using type = typename detail::ComposeArgs<0, double, TypeList<>>::args;
            THEN("should padding nothing") {
                REQUIRE(std::is_same_v<TypeList<double>, type>);
            }
        }

        WHEN("compose the 0 parameter with non-empty list") {
            using type = typename detail::ComposeArgs<0, double, TypeList<int>>::args;
            THEN("should padding nothing") {
                REQUIRE(std::is_same_v<TypeList<int, double>, type>);
            }
        }

        WHEN("compose the 3rd parameter") {
            using type = typename detail::ComposeArgs<2, double, TypeList<>>::args;
            THEN("should padding 2 void") {
                REQUIRE(std::is_same_v<TypeList<void, void, double>, type>);
            }
        }

        WHEN("compose the 3rd parameter with non-empty") {
            using type = typename detail::ComposeArgs<2, double, TypeList<int>>::args;
            THEN("should padding 2 void") {
                REQUIRE(std::is_same_v<TypeList<int, void, void, double>, type>);
            }
        }

    }

    SCENARIO("CalcArgs") {

        GIVEN("bind the 0, 3") {
            using type = detail::CalcArgs<TypeList<>, 0, 0, _0_, int, _3_, double>;
            THEN("the number should be 2") {
                REQUIRE(type::actualNum == 2);
            }
            THEN("the result args should be padded 2 void") {
                REQUIRE(std::is_same_v<type::args, TypeList<int, void, void, double>>);
            }
        }

        GIVEN("bind the 1, 3") {
            using type = detail::CalcArgs<TypeList<>, 0, 0, _1_, int, _3_, double>;
            THEN("the number should be 2") {
                REQUIRE(type::actualNum == 2);
            }
            THEN("the result args should be padded 2 void") {
                REQUIRE(std::is_same_v<type::args, TypeList<void, int, void, double>>);
            }
        }
    }

    SCENARIO("Combine") {
        //using type = typename Bind<Foo, _1_, int, _3_, double>::template type<char, float>;
        using type = Combine<Foo, TypeList<int, double>, TypeList<void, char, void, long>>;
        REQUIRE(std::is_same_v<typename type::type<float>, Foo<int, char, double, long, float>>);
    }

    SCENARIO("DoBind") {
        using bind = detail::DoBind<Foo, 2, TypeList<void, char, void, long>>;
        using BindResult = typename bind::template apply<int, double, float>;
        REQUIRE(std::is_same_v<BindResult, Foo<int, char, double, long, float>>);
    }

    SCENARIO("Bind") {
        using Bound = Bind<Foo, _1_, int, _3_, double>;
        WHEN("apply a bound template directly") {
            using type = typename Bound::template apply<char, float, long>;
            THEN("should put the applied types in correct position") {
                REQUIRE(std::is_same_v<type, Foo<char, int, float, double, long>>);
            }
        }

        WHEN("pass it to a type list") {
            using type = decltype(TypeList<char, float, long>::exportTo<__TL_bind(Foo, _1_, int, _3_, double)>());
            REQUIRE(std::is_same_v<type, Foo<char, int, float, double, long>>);
        }
    }
}