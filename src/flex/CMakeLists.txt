find_package(BISON REQUIRED)
set(BISON_GENERATE_DEFINES TRUE)
find_package(FLEX REQUIRED)

BISON_TARGET(PARSER ${CMAKE_CURRENT_SOURCE_DIR}/parser_cool.yyp ${CMAKE_CURRENT_BINARY_DIR}/parser_cool.cpp
COMPILE_FLAGS --defines="${CMAKE_CURRENT_BINARY_DIR}/parser_cool.hpp")
FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/scanner_cool.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(SCANNER PARSER)

add_library(flex STATIC ${BISON_PARSER_OUTPUTS} ${FLEX_SCANNER_OUTPUTS})
target_link_libraries(flex ast)
