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
        std::cout << "Failed to initialize GLAD" << '\n';
    }
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
    camera->ResetProjMatrix(x/y); 
}

void Renderer::Clear(float r, float g, float b, float alpha)
{
    glClearColor(0.6f, 0.0f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::update()
{
}
