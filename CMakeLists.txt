project(vulktest CXX)
cmake_minimum_required(VERSION 3.13.2) 
add_subdirectory(core)
add_executable(vulktest main.cpp)

target_link_libraries(vulktest vulk_core)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT vulktest )

set_target_properties(vulktest PROPERTIES CXX_STANDARD 17)