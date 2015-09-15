cmake_minimum_required(VERSION 3.0)

project("bake")

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS "-g -Wall")

add_subdirectory(src)