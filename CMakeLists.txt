cmake_minimum_required (VERSION 3.8)
set(PROJECTNAME VulkanProject)
project(${PROJECTNAME} C CXX)

set_property(
    GLOBAL PROPERTY USE_FOLDERS ON
    GLOBAL PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME}
    )

add_subdirectory(code)

# set variables
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty")

find_package(Vulkan REQUIRED)
set(VULKAN_GLSL_COMPILER "${Vulkan_INCLUDE_DIRS}/../Bin/glslangValidator.exe")

set_target_properties(${PROJECTNAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories("${PROJECTNAME}"
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${THIRD_PARTY_DIR}/glm/0.9.8.4" 
        "${THIRD_PARTY_DIR}/glfw/3.2.1.x64/include"
        ${Vulkan_INCLUDE_DIRS}
    )

target_link_libraries(${PROJECTNAME} glfw3 ${Vulkan_LIBRARIES})
