cmake_minimum_required(VERSION 3.3)

project("lab1")

find_package(FLEX)
LIST(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
FIND_LIBRARY(FL_LIBRARY NAMES libfl fl DOC "path to the fl library")

FLEX_TARGET(MyScanner code/src/cool.l code/src/lex.yy.cpp)

add_executable(bake src/driver.cpp code/src/lex.yy.cpp ${FLEX_MyScanner_OUTPUTS})