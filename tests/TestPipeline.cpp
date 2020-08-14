////
//// Created by godsme on 7/15/20.
////
//
//#include <type-list/algo/PipeLine.h>
//#include <type-list/algo/Take.h>
//#include <type-list/types/List.h>
//
//#include <type_traits>
//#include <catch.hpp>
//
//namespace {
//    using namespace TYPE_LIST_NS;
//
//
//    template<typename T> struct S;
//    SCENARIO("value pipe line") {
//        using type = __TL_pipeline
//            ( __TL_infinite(1)
//            , __TL_take(10)
//            , __TL_filter([](auto v) {
//                return v % 2 == 0; })
//            , __TL_sort([](auto lhs, auto rhs) {
//                return lhs > rhs; })
//            , __TL_map([](auto v) {
//                return v + 1; })
//            , __TL_drop(2)
//            );
//
//        REQUIRE(std::is_same_v<__TL_list(7,5,3), type>);
//    }
//
//    template<typename T1, typename T2>
//    struct Take {
//        constexpr static bool value = true;
//    };
//
//    template<typename T1, typename T2>
//    using Take_t = Take<T1, T2>;
//
//    SCENARIO("value pipe line 1") {
//        using type = __TL_pipeline
//        ( __TL_list(1, 2, 3, 4, 5)
//        , __TL_drop(2)
//        , __TL_take(1)
//        );
//    }
//}