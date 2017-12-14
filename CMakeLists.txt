project(vulktest C CXX)
cmake_minimum_required(VERSION 3.8) 
add_subdirectory(core)
add_executable(vulktest main.cpp)
target_link_libraries(vulktest vulk_core)

add_definitions(-DENGINEROOT="${CMAKE_CURRENT_SOURCE_DIR}")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vulktest)