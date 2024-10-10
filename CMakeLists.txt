cmake_minimum_required(VERSION 3.2)

project(sort_avl_quick)

add_executable(main.cpp quickSort.hpp avlTree.hpp)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")