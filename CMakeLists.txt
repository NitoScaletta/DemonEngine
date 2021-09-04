cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)
#include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories(include/)
include_directories(src/include/)
include_directories(vendor/imgui/)


#GLFW config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

add_library(GLAD      vendor/GLAD/src/glad.c)
add_library(Shader    src/Shader.cpp)
add_library(glObjects src/glObjects.cpp)
add_library(stb_image src/image.cpp)
add_library(renderer  src/renderer.cpp)
add_library(core      src/CoreFun.cpp
                      src/Cube.cpp
                      src/Light.cpp)

add_library(camera src/Camera.cpp)

add_library(imgui   vendor/imgui/imgui.cpp
                    vendor/imgui/imgui_tables.cpp
                    vendor/imgui/imgui_draw.cpp
                    vendor/imgui/imgui_widgets.cpp
                    vendor/imgui/imgui_demo.cpp
                    vendor/imgui/backends/imgui_impl_opengl3.cpp
                    vendor/imgui/backends/imgui_impl_glfw.cpp
                    )

add_library(test    src/testClearColor.cpp
                    src/test.cpp
                    src/test/TestLight.cpp
                    src/test/TestDirLight.cpp

                    )
#exec
a.out.outdd_executable (LearnOpenGL src/app.cpp)



#link delle librerie
target_link_libraries(LearnOpenGL   libGL.so
                                    glfw
                                    GLAD
                                    Shader
                                    glObjects
                                    stb_image
                                    renderer
                                    imgui
                                    test
                                    core
                                    camera
                                    )

target_link_libraries(renderer      GLAD
                                    Shader
                                    glObjects
                                    )

