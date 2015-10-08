add_subdirectory(ast)
add_subdirectory(typecheck)
add_subdirectory(flex)

add_executable(bake driver.cpp)

target_link_libraries(bake typecheck ast flex)
