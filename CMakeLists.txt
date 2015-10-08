cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-std=c++11 -g -Wall -Wno-deprecated-register)

project(bake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bake_SOURCE_DIR})


add_subdirectory(lib/googletest-release-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)
