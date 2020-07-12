cmake_minimum_required(VERSION 3.16)
project(type_list)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

#add_library(type_list
#        include/type-list/type-list-ns.h
#        include/type-list/TypeList.h)

add_executable(type-list-test
        tests/catch.cpp
        tests/TestTypeList.cpp include/type-list/base/Signatures.h include/type-list/concept/NonEmptyListConcept.h include/type-list/concept/ExportableListConcept.h include/type-list/concept/ListConcept.h include/type-list/base/ValueList.h include/type-list/concept/AppendableTypeListConcept.h)