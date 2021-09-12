#include "include/renderer.h"
#include "include/glObjects.h"
#include "include/Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>


void Renderer::draw(VertexArray& vao, ElementBuffer& ebo, ShaderProgram& ps )
{
    vao.bind();
    ebo.bind();
    ps.use();
    glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr );
}

void Renderer::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}


GLFWwindow* Renderer::CreateWindow(unsigned int x, unsigned int y)
{
    bool block_cursor = true;
    GLFWwindow *window;
    if (!glfwInit())
    {
        std::cout << "errore" << std::endl;
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(x, y, "DemonEngine", NULL, NULL);
    if (!window)
    {
        std::cout << "Impossibile creare finestra glfw" << std::endl;
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    wind = window;
    return window;
}


void Renderer::update()
{
    if(glfwGetKey(wind, GLFW_KEY_P) == GLFW_PRESS)
        glfwSetInputMode(wind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if(glfwGetKey(wind, GLFW_KEY_O) == GLFW_PRESS)
        glfwSetInputMode(wind, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
