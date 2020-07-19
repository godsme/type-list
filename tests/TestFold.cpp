//
// Created by godsme on 7/19/20.
//

#include <type-list/algo/Fold.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

#define ASSERT_EQ_T(a, b) REQUIRE(std::is_same_v<a, b>)

    __TL_lambda(Add, size_t ACC, typename T)
    __return_v(ACC + sizeof(T));

    __TL_lambda(AddValue, size_t ACC, size_t V)
    __return_v(ACC + V);

    SCENARIO("foldl an empty list with FoldL") {
        using type = __TL_FoldL(__TL_list(), Add, 0);
        REQUIRE(type::value == 0);
    }

    SCENARIO("foldl a non-empty list with FoldL") {
        using type = __TL_FoldL(__TL_list(1,2,3), AddValue, 0);
        REQUIRE(type::value == 6);
    }

    template<typename ... Ts>
    struct Composer {
        template <typename T>
        using append = Composer<Ts..., T>;

        using type = Composer<Ts...>;
    };

    template<auto V> struct MyTrait {
        using type = void;
    };

    template<> struct MyTrait<1> {
        using type = int;
    };

    template<> struct MyTrait<2> {
        using type = long;
    };

    template<typename T, auto V>
    struct ToTypeList {
        using t = typename MyTrait<V>::type;
        using type = typename T::template append<t>::type;
    };

    SCENARIO("foldl a non-empty value list to type with FoldL") {
        using type = __TL_FoldL(__TL_list(1,2,3), ToTypeList, Composer<>);
        using result = Composer<int, long, void>;
        ASSERT_EQ_T(type::type, result);
    }

    SCENARIO("foldl a non-empty Type list with FoldL") {
        using type = __TL_FoldL(__TL_list(int,double,char), Add, 0);
        REQUIRE(type::value == sizeof(int) + sizeof(double) + sizeof(char));
    }

    template <typename T> struct MyTypeTrait {
        using type = void;
    };

    template <> struct MyTypeTrait<int> {
        using type = long;
    };

    template <> struct MyTypeTrait<char> {
        using type = double;
    };

    template<typename COMPOSER, typename T>
    struct Transformer {
        using type = typename COMPOSER::template append<typename MyTypeTrait<T>::type>;
    };

    SCENARIO("foldl a non-empty Type list to Type List with FoldL") {
        using result = __TL_FoldL(__TL_list(int,double,char), Transformer, Composer<>);
        using expected = Composer<long, void, double>;
        //ASSERT_EQ_T(result::type, expected);
    }
}