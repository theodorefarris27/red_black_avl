cmake_minimum_required(VERSION 4.0)
project(red_black_avl)

set(CMAKE_CXX_STANDARD 20)

add_executable(red_black_avl main.cpp
        includes/tree_node/tree_node.h
        includes/red_black_avl/avl_functions.h
        includes/red_black_avl/avl.h)
