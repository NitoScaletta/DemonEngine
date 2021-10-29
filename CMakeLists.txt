cmake_minimum_required(VERSION 3.16)
project(DemonEngine)
set (CMAKE_CXX_STANDARD 20)
#include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories(include/)
include_directories(src/include/)
include_directories(src/test/include/)
include_directories(vendor/imgui/)
include_directories(vendor/GLAD/include/)
include_directories(vendor/assimp/include/)


#GLFW config
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#ASSIMP
SET (ASSIMP_BUILD_TESTS OFF)



add_subdirectory(vendor/glfw)
#add_subdirectory(vendor/assimp)

# set_property(TARGET assimp PROPERTY CMAKE_CXX_STANDARD 20)


add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_library(GLAD      vendor/GLAD/src/glad.c)
add_library(Shader    src/Shader.cpp)
add_library(glObjects src/glObjects.cpp)
add_library(stb_image src/image.cpp)
add_library(renderer  src/renderer.cpp)
add_library(core      src/CoreFun.cpp
                      src/Cube.cpp
                      src/Light.cpp
                      src/Timer.cpp
                      #src/Mesh.cpp
                      )

add_library(camera  src/Camera.cpp
                    src/Camera2d.cpp)

add_library(imgui   vendor/imgui/imgui.cpp
                    vendor/imgui/imgui_tables.cpp
                    vendor/imgui/imgui_draw.cpp
                    vendor/imgui/imgui_widgets.cpp
                    vendor/imgui/imgui_demo.cpp
                    vendor/imgui/backends/imgui_impl_opengl3.cpp
                    vendor/imgui/backends/imgui_impl_glfw.cpp
                    )
                    

add_library(test    src/test.cpp
                    src/test/TestMultiLight.cpp
                    src/test/TestBatch.cpp
                    )
#exec
add_executable (DemonEngine src/app.cpp)



#link delle librerie
target_link_libraries(DemonEngine  opengl32.lib
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

