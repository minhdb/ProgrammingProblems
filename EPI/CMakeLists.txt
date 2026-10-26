cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g")

project(EPI)

# set(DATA_STRUCTURES ./data_structures/singly_linked_node.h ./data_structures/singly_linked_node.cc ./data_structures/bst_node.h)

# add_library(data_structures ${DATA_STRUCTURES})

# add_subdirectory(./linked_list_problems ./build/linked_list_problems )
# add_subdirectory(./ad_hoc ./build/ad_hoc)
# add_subdirectory(./stack_problems ./build/stack_problems)
# add_subdirectory(./object_oriented_design ./build/object_oriented_design)

add_subdirectory(./ch05_primitive_types ./build/ch05_primitive_types)
add_subdirectory(./misc_practice ./build/misc_practice)
add_subdirectory(./ch06_arrays ./build/ch06_arrays)
add_subdirectory(./ch07_strings ./build/ch07_strings)
add_subdirectory(./ch08_linked_lists ./build/ch08_linked_lists)
add_subdirectory(./ch09_stacks_and_queues ./build/ch09_stacks_and_queues)
add_subdirectory(./ch10_binary_trees ./build/ch10_binary_trees)
add_subdirectory(./ch11_heaps ./build/ch11_heaps)
add_subdirectory(./ch12_searching ./build/ch12_searching)
add_subdirectory(./ch13_hash_tables ./build/ch13_hash_tables)
add_subdirectory(./ch14_sorting ./build/ch14_sorting)
add_subdirectory(./ch15_binary_search_trees ./build/ch15_binary_search_trees)
add_subdirectory(./ch16_recursion ./build/ch16_recursion)
add_subdirectory(./ch17_dp ./build/ch17_dp)
add_subdirectory(./ch18_greedy_invariants ./build/ch18_greedy_invariants)
add_subdirectory(./ch19_graphs ./build/ch19_graphs)
