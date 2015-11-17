add_subdirectory(ast)
add_subdirectory(typecheck)
add_subdirectory(flex)
add_subdirectory(ir)

add_library(driver STATIC driver.cpp)

add_executable(bake main.cpp)

target_link_libraries(bake driver typecheck ast flex ir)
