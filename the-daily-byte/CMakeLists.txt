cmake_minimum_required(VERSION 3.10)

project(daily_bytes)

set (CMAKE_CXX_STANDARD 14)

set(SINGLY_LINKED_LIST ./data_structures/singly_linked_node.h ./data_structures/singly_linked_node.cc)
# set(BST_NODE ./data_structures/bst_node.h)

add_library(singly_linked_list ${SINGLY_LINKED_LIST})
# add_library(bst_node ${BST_NODE})

add_subdirectory(./linked_list_problems ./build/linked_list_problems )
add_subdirectory(./ad_hoc ./build/ad_hoc)
add_subdirectory(./stack_problems ./build/stack_problems)
add_subdirectory(./object_oriented_design ./build/object_oriented_design)
add_subdirectory(./tree_problems ./build/tree_problems)
add_subdirectory(./recursion ./build/recursion)
add_subdirectory(./graph_problems ./build/graph_problems)
add_subdirectory(./greedy_problems ./build/greedy_problems)
add_subdirectory(./dynamic_programming ./build/dynamic_programming)
