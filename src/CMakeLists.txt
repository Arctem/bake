find_package(FLEX REQUIRED)

FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/cool.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

add_executable( bake
    driver.cpp
    ${FLEX_SCANNER_OUTPUTS}
 )
