//
// Created by godsme on 7/12/20.
//

#include <type-list/algo/Transform.h>
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

    template<int I> struct Add {
        constexpr static int value = I + 10;
    };

    template <typename T> struct S;
    SCENARIO("Transform ValueToValue") {
        using type = TransformValue_t<ValueList<1,2,3>, Add>;
        REQUIRE(std::is_same_v<ValueList<11,12,13>, type>);
    }

    template<auto I> struct W;
    template<auto I> struct ToType {
        using type = W<I>;
    };

    SCENARIO("Transform ValueToType") {
        using type = TransformValue_t<ValueList<1,2,3>, ToType>;
        REQUIRE(std::is_same_v<TypeList<W<1>,W<2>,W<3>>, type>);
    }

    template<typename T> struct WT;
    template<typename T> struct Identity {
        using type = WT<T>;
    };
    SCENARIO("Transform Type2Type") {
        using type = Transform_t<TypeList<int, double>, Identity>;
        REQUIRE(std::is_same_v<TypeList<WT<int>,WT<double>>, type>);
    }

    template<typename T> struct IntTrait {
        constexpr static bool value = std::is_integral_v<T>;
    };
    SCENARIO("Transform Type2Value") {
        using type = Transform_t<TypeList<int, double>, IntTrait>;
        REQUIRE(std::is_same_v<ValueList<true, false>, type>);
    }
}