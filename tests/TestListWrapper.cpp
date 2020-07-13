//
// Created by godsme on 7/12/20.
//

#include <type-list/types/ListWrapper.h>
#include <type-list/concept/ValueListConcept.h>
#include <type-list/concept/ExportableListConcept.h>
#include <type-list/concept/NonEmptyListConcept.h>
#include <type-list/types/ValueList.h>
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
    SCENARIO("ValueListWrapper") {
        using type = List<ValueList<1,2,3>>;
        //using type = Transform_t<TypeList<int, double>, Identity>;
        //S<type> ss;
        THEN("it has a head") {
            REQUIRE(std::is_same_v<type::Head, Value<1>>);
        }
    }
}