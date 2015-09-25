find_package(FLEX REQUIRED)

FLEX_TARGET(SCANNER ${CMAKE_CURRENT_SOURCE_DIR}/scanner_cool.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

#enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(EXECUTABLE_OUTPUT_PATH ../..)
add_executable( bake
    driver.cpp
    ${FLEX_SCANNER_OUTPUTS}
 )

 #target_link_libraries(bake ${GTEST_BOTH_LIBRARIES})
 #add_test(AllTestsInBake bake)
