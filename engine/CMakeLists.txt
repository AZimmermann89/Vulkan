set(LIBNAME vulk_engine)
project(${LIBNAME} CXX)

find_package(Vulkan REQUIRED)

set(VULKAN_GLSL_COMPILER "${Vulkan_INCLUDE_DIRS}/../Bin/glslangValidator.exe")

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

add_library(${LIBNAME} STATIC ${CORE} ${SHADERS} ${Vulkan_INCLUDE_DIRS})

set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories("${LIBNAME}"
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${Vulkan_INCLUDE_DIRS}
    )

target_link_libraries(${LIBNAME} glfw3 glm ${Vulkan_LIBRARIES})

