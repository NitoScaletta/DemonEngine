#include "Renderer/renderer.h"
#include "graphic/glObjects.h"
#include "graphic/Shader.h"
#include <iostream>

Renderer::Renderer(float x, float y) : wind_size_x(x), wind_size_y(y) 
{
    camera = new Camera2d(wind_size_x/wind_size_y);
}

Renderer::~Renderer() 
{
    delete camera;
}

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
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Renderer::End() 
{
    glfwSwapBuffers(wind);
    glfwPollEvents();
}

void Renderer::ImGuiInit() 
{
    const char* glsl_version = "#version 430";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(wind, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Renderer::ImGuiStart()
{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
}

void Renderer::ImGuiEnd() 
{
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::ImGuiClose() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::updateResolution(const float x, const float y) 
{
    wind_size_x = x; 
    wind_size_y = y; 
    camera->ResetProjMatrix(x/y); 
}

GLFWwindow* Renderer::WindowInit()
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
    window = glfwCreateWindow(wind_size_x, wind_size_y, "DemonEngine", NULL, NULL);
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

void Renderer::Clear(float r, float g, float b, float alpha)
{
    glClearColor(0.6f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update()
{
}
