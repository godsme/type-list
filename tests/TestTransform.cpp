//
// Created by godsme on 7/12/20.
//

#include <type-list/algo/Transform.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/List.h>
#include <type-list/types/Lambda.h>
#include <type_traits>
#include <cstdint>
#include <catch.hpp>

namespace {
    using namespace TYPE_LIST_NS;

    __TL_lambda(Some, __TL_lambda(F, __Set(), int))
    __return_t(F<int, 0>);

    __TL_lambda(Add, int I) __return_v(I + 10);

    template <typename T> struct S;
    SCENARIO("Transform ValueToValue") {
        using type = __TL_Map(__TL_list(1, 2, 3), Add);
        REQUIRE(std::is_same_v<ValueList<11,12,13>, type>);
    }

    __TL_lambda(W, auto I);
    __TL_lambda(ToType, auto I) __return_t(W<I>);
    SCENARIO("Transform ValueToType") {
        using type = __TL_Map(__TL_list(1, 2, 3), ToType);
        REQUIRE(std::is_same_v<TypeList<W<1>,W<2>,W<3>>, type>);
    }

    __TL_lambda(WT, __Set(T));
    __TL_lambda(Wrap, __Set(T)) __return_t(WT<T>);

    SCENARIO("Transform Type2Type") {
        using type = __TL_Map(__TL_list(int, double), Wrap);
        REQUIRE(std::is_same_v<TypeList<WT<int>,WT<double>>, type>);
    }

    __TL_lambda(IntTrait, __Set(T)) __return_v(std::is_integral_v<T>);
    SCENARIO("Transform Type2Value") {
        using type = __TL_Map(__TL_list(int, double), IntTrait);
        REQUIRE(std::is_same_v<ValueList<true, false>, type>);
    }

    constexpr auto add(int i) { return i + 10; };
    SCENARIO("Transform Type2Value by function") {
        using type = __TL_Map(__TL_list(1, 2), add);
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }

    SCENARIO("Transform Type2Value by direct lambda") {
        using type = __TL_Map(__TL_list(1, 2), [](int i) { return i + 10; });
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }

    SCENARIO("Transform Type2Value by indirect lambda") {
        constexpr auto l = [](int i) { return i + 10; };
        using type = __TL_Map(__TL_list(1, 2), l);
        REQUIRE(std::is_same_v<ValueList<11, 12>, type>);
    }
}