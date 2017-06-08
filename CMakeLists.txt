project(vulktest C CXX)
cmake_minimum_required(VERSION 3.8) 
add_subdirectory(lib)
add_executable(vulktest main.cpp)
target_link_libraries(vulktest vulk_engine)

set_property(
    GLOBAL PROPERTY VS_STARTUP_PROJECT vulktest
    GLOBAL PROPERTY USE_FOLDERS ON
)