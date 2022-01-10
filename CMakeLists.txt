cmake_minimum_required(VERSION 3.16)
project(DemonEngine)
set (CMAKE_CXX_STANDARD 20)

include_directories(src/include/)
include_directories(src/test/)
include_directories(src/Editor/)
include_directories(vendor/imgui/)
include_directories(vendor/imgui/backends/)
include_directories(vendor/GLAD/include/)
include_directories(vendor/spdlog/include/)
include_directories(vendor/glm/)
include_directories(vendor/entt/single_include/)


file (GLOB Renderer     "src/Renderer/*.cpp")
file (GLOB core         "src/core/*.cpp" "src/core/profiling/*.cpp")
file (GLOB Editor       "src/Editor/*.cpp")

####################################################################
########## EXTERNAL LIBS ###########################################
####################################################################
#GLFW config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

#IMGUI config
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

#######################################################################
######################################################################

add_library(GLAD        vendor/GLAD/src/glad.c)
add_library(stb_image   src/image.cpp)
add_library(core        ${core})
add_library(renderer    ${Renderer})

add_library(imgui   vendor/imgui/imgui.cpp
                    vendor/imgui/imgui_tables.cpp
                    vendor/imgui/imgui_draw.cpp
                    vendor/imgui/imgui_widgets.cpp
                    vendor/imgui/imgui_demo.cpp
                    vendor/imgui/backends/imgui_impl_opengl3.cpp
                    vendor/imgui/backends/imgui_impl_glfw.cpp
                    )



add_executable (DemonEngine ${Editor} "src/test/TestRenderBatch.cpp")


#link delle librerie
target_link_libraries(DemonEngine   opengl32.lib
                                    glfw
                                    GLAD
                                    stb_image
                                    renderer
                                    imgui
                                    core
                                    )

target_link_libraries(renderer      GLAD
                                    )

