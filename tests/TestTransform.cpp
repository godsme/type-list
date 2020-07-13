//
// Created by godsme on 7/12/20.
//

#include <type-list/algo/Transform.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/base/List.h>

#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    template<int I> struct Add {
        constexpr static int value = I + 10;
    };

    template <typename T> struct S;
    SCENARIO("Transform ValueToValue") {
        using type = __TL_map(__TL_list(1, 2, 3), Add);
        REQUIRE(std::is_same_v<ValueList<11,12,13>, type>);
    }

    template<auto I> struct W;
    template<auto I> struct ToType {
        using type = W<I>;
    };

    SCENARIO("Transform ValueToType") {
        using type = __TL_map(__TL_list(1, 2, 3), ToType);
        REQUIRE(std::is_same_v<TypeList<W<1>,W<2>,W<3>>, type>);
    }

    template<typename T> struct WT;
    template<typename T> struct Identity {
        using type = WT<T>;
    };
    SCENARIO("Transform Type2Type") {
        using type = __TL_map(__TL_list(int, double), Identity);
        REQUIRE(std::is_same_v<TypeList<WT<int>,WT<double>>, type>);
    }

    template<typename T> struct IntTrait {
        constexpr static bool value = std::is_integral_v<T>;
    };
    SCENARIO("Transform Type2Value") {
        using type = __TL_map(__TL_list(int, double), IntTrait);
        REQUIRE(std::is_same_v<ValueList<true, false>, type>);
    }

    constexpr auto add(int i) { return i + 10; };

    SCENARIO("Transform Type2Value by function") {
        using type = __TL_map(__TL_list(1, 2), add);
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }

    SCENARIO("Transform Type2Value by direct lambda") {
        using type = __TL_map(__TL_list(1, 2), [](int i) { return i + 10; });
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }

    SCENARIO("Transform Type2Value by indirect lambda") {
        constexpr auto l = [](int i) { return i + 10; };
        using type = __TL_map(__TL_list(1, 2), l);
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }

//    SCENARIO("Transform Type2Value by indirect lambda") {
//        constexpr auto l = [](int i) { return i + 10; };
//        using type = __TL_transform(__TL_infinite(1), l);
//        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
//    }
}