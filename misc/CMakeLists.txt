cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g")

project(ActualCodingProblems)

# set(DATA_STRUCTURES ./data_structures/singly_linked_node.h ./data_structures/singly_linked_node.cc ./data_structures/bst_node.h)

# add_library(data_structures ${DATA_STRUCTURES})

# add_subdirectory(./linked_list_problems ./build/linked_list_problems )
# add_subdirectory(./ad_hoc ./build/ad_hoc)
# add_subdirectory(./stack_problems ./build/stack_problems)
# add_subdirectory(./object_oriented_design ./build/object_oriented_design)

add_executable(HRT_Task1 HRT_Task1.cc)
add_executable(HRT_Task2 HRT_Task2.cc)
add_executable(HRT_Task3 HRT_Task3.cc)
add_executable(OCVM OCVM.cc)
add_executable(convex_hull convex_hull.cc)
