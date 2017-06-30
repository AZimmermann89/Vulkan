set(LIBNAME vulk_core)
project(${LIBNAME} CXX)

find_package(Vulkan REQUIRED)

set(VULKAN_GLSL_COMPILER "${Vulkan_INCLUDE_DIRS}/../Bin/glslangValidator.exe")

set(CORE core.h core.cpp)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

add_library(${LIBNAME} STATIC ${CORE} ${Vulkan_INCLUDE_DIRS})

set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories("${LIBNAME}"
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${Vulkan_INCLUDE_DIRS}
    )

target_link_libraries(${LIBNAME} glfw glm ${Vulkan_LIBRARIES})

