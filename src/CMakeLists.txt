find_package(BISON REQUIRED)
set(BISON_GENERATE_DEFINES TRUE)
find_package(FLEX REQUIRED)
set(EXECUTABLE_OUTPUT_PATH ../..)

BISON_TARGET(PARSER ${CMAKE_CURRENT_SOURCE_DIR}/parser_cool.yyp ${CMAKE_CURRENT_BINARY_DIR}/parser_cool.cpp
COMPILE_FLAGS --defines="${CMAKE_CURRENT_BINARY_DIR}/parser_cool.h")
FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/flex/scanner_cool.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(SCANNER PARSER)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(flex)
add_subdirectory(ast)

set(EXECUTABLE_OUTPUT_PATH ../..)

add_executable(bake
    driver.cpp
    ${BISON_PARSER_OUTPUTS}
    ${FLEX_SCANNER_OUTPUTS}
)
target_link_libraries(bake ast)

 #target_link_libraries(bake.exe ${GTEST_BOTH_LIBRARIES})
 #add_test(AllTestsInBake bake)
