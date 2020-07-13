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
    template<typename T> struct Wrapper;
    template<typename T> struct Identity {
        using type = Wrapper<T>;
    };
    template <typename T> struct S;
    SCENARIO("Transform ValueList") {
        using type = TransformValue_t<ValueList<1,2,3>, Add>;
        //using type = Transform_t<TypeList<int, double>, Identity>;
        REQUIRE(std::is_same_v<ValueList<11,12,13>, type>);
    }
}