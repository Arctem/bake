cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-std=c++11 -g -Wall -Wno-deprecated-register)

project(bake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bake_SOURCE_DIR})

add_subdirectory(lib/googletest-release-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

macro(create_test target)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bake_SOURCE_DIR}/bin)
  add_executable(${target} ${target}.cpp)
  target_link_libraries(${target} gtest gtest_main)
  if(DEFINED ENV{CIRCLE_TEST_REPORTS})
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}> --gtest_output=xml:$ENV{CIRCLE_TEST_REPORTS}/${target}/)
  else()
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}> --gtest_output=xml:${bake_SOURCE_DIR}/test_out/${target}/)
  endif()
endmacro(create_test)

include_directories(include)
add_subdirectory(src)

