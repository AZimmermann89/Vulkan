set(LIBNAME vulk_core)
project(${LIBNAME} CXX)


find_package(Vulkan REQUIRED)

set(VULKAN_GLSL_COMPILER "${Vulkan_INCLUDE_DIRS}/../Bin/glslangValidator.exe")

set(CORE 
    RenderCore.h
    RenderCore.cpp
 )

 set(SHADER
    shaders/shader.frag
    shaders/shader.vert
    shaders/compile.bat
 )

 source_group(core FILES ${CORE})
 source_group(shaders FILES ${SHADER})

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

add_library(${LIBNAME} STATIC ${CORE} ${Vulkan_INCLUDE_DIRS} ${SHADER})

add_definitions(-DENGINEROOT="${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories("${LIBNAME}"
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${Vulkan_INCLUDE_DIRS}
    )

target_link_libraries(${LIBNAME} glfw glm ${Vulkan_LIBRARIES})

