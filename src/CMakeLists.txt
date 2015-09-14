find_package(FLEX)

FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/cool.l ${CMAKE_CURRENT_SOURCE_DIR}/driver.cpp)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

add_executable( bake
    driver.cpp
    ${FLEX_MyScanner_OUTPUTS}
 )
