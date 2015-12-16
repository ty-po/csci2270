# This file is released without license and may be used freely
# Author: Alec Thilenius - alec@thilenius.com

cmake_minimum_required (VERSION 2.6)
project (binary_tree)

set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Threads REQUIRED)
include(ExternalProject)

#===  VANGAURD 0.1.0  ==========================================================
ExternalProject_Add(
    vanguard
    URL https://s3-us-west-1.amazonaws.com/thilenius.misc/vanguard-0.1.1.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/vanguard
    # Don't install
    INSTALL_COMMAND ""
)

# Create a target library for Vanguard
add_library(libvanguard IMPORTED STATIC GLOBAL)
add_dependencies(libvanguard vanguard)

# Define the Vanguard lib
ExternalProject_Get_Property(vanguard source_dir binary_dir)
include_directories("${source_dir}")
set_target_properties(libvanguard PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/libvanguard.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

#===  BINARY TREE  =============================================================
add_executable (
  binary_tree
  binary_tree.cc
  binary_tree_test.cc
)
add_dependencies(binary_tree vanguard)
target_link_libraries (
  binary_tree
  ${CMAKE_THREAD_LIBS_INIT}
  libvanguard
)
