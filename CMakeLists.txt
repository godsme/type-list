cmake_minimum_required(VERSION 3.16)
project(type_list)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

add_executable(type-list-test
        tests/catch.cpp
        tests/TestTypeList.cpp include/type-list/types/Signatures.h include/type-list/concept/NonEmptyListConcept.h include/type-list/concept/ExportableListConcept.h include/type-list/concept/ListConcept.h include/type-list/types/ValueList.h include/type-list/concept/AppendableTypeListConcept.h include/type-list/algo/Transform.h tests/TestValueList.cpp include/type-list/concept/ValueListConcept.h include/type-list/concept/TypeListConcept.h tests/TestTransform.cpp include/type-list/types/Value.h tests/TestListWrapper.cpp include/type-list/types/List.h include/type-list/algo/Drop.h tests/TestDrop.cpp tests/TestInfiniteList.cpp tests/TestEmptyList.cpp include/type-list/algo/Take.h tests/TestTake.cpp include/type-list/types/Lambda.h include/type-list/algo/Filter.h tests/TestFilter.cpp include/type-list/algo/Sort.h tests/TestSort.cpp include/type-list/algo/PipeLine.h tests/TestPipeline.cpp include/type-list/algo/Curry.h tests/TestCurry.cpp include/type-list/algo/Bind.h tests/TestBind.cpp include/type-list/algo/Group.h tests/TestGroup.cpp include/type-list/types/EmptyList.h include/type-list/algo/Compose.h include/type-list/concept/CallableConcept.h include/type-list/types/TemplateDeduce.h include/type-list/algo/Fold.h tests/TestFold.cpp include/type-list/types/TypeValueTrait.h include/type-list/algo/Unique.h include/type-list/algo/Elem.h include/dsl/NodeTraits.h include/dsl/Node.h include/dsl/Link.h tests/TestDsl.cpp)