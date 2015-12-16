cmake_minimum_required (VERSION 2.6)
project (linked_list)

set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable (
  stack_queue
  stack_queue.cc
  linked_list.cc
)

