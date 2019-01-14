set(LIBNAME vulk_core)
project(${LIBNAME} CXX)

find_package(Vulkan REQUIRED)

set(VULKAN_GLSL_COMPILER "${Vulkan_INCLUDE_DIRS}/../Bin/glslangValidator.exe")

set(CORE 
    code/RenderCore.h
    code/RenderCore.cpp
)

set(SHADER
    shaders/shader.frag
    shaders/shader.vert
)

set(ADDITIONAL_INCLUDES
    thirdparty/stb
)

source_group(core FILES ${CORE})
source_group(shaders FILES ${SHADER})

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/tinyobjloader)

add_library(${LIBNAME} STATIC ${CORE} ${Vulkan_INCLUDE_DIRS} ${SHADER})

target_include_directories("${LIBNAME}"
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}  ${ADDITIONAL_INCLUDES}
)

add_definitions(-DENGINEROOT="${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(${LIBNAME} PROPERTIES LINKER_LANGUAGE CXX
                                            CXX_STANDARD 17
                                            CXX_STANDARD_REQUIRED ON
                                            CXX_EXTENSIONS OFF
                                            )


target_include_directories("${LIBNAME}"
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(${LIBNAME} glfw glm tinyobjloader ${Vulkan_LIBRARIES})