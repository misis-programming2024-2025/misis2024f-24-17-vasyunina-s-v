cmake_minimum_required(VERSION 3.10)

project(misis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(doctest)

add_subdirectory(first_class)
add_subdirectory(complex_prj)
add_subdirectory(rational_prj)
add_subdirectory(dynamic_array_prj)
add_subdirectory(StackArrT)
add_subdirectory(stack_base_prj)
add_subdirectory(stack_lst_prj)