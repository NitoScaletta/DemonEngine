#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "include/Renderer/Shader.h"
#include "include/Renderer/glObjects.h"
#include "stb_image.h"
#include "include/renderer.h"
#include <math.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const unsigned int SCR_X =1024;
const unsigned int SCR_Y = 768;
const float scr_x = SCR_X;
const float scr_y = SCR_Y;



void processInput(GLFWwindow *window )
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

int main(void)
{
    Renderer renderer;
    GLFWwindow* window;
    const char* glsl_version = "#version 130";


    float vertices[] =
    {
     50.0f,  50.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
     150.0f, 50.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
     150.0f, 150.0f,1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
     50.0f,  150.0f,1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f
    };


    Vertex v[3];
    v[0].setPos(10, 10, 1);
    v[0].setCol(0.5f, 0.5f, 0.5f, 1.0f);
    v[0].setTCor(0.0f, 0.0f);
    v[0].textID = 1.0f;
    v[1].setPos(50, 10, 1);
    v[1].setCol(0.5f, 0.5f, 0.5f, 1.0f);
    v[1].setTCor(0.0f, 0.0f);
    v[1].textID = 1.0f;
    v[2].setPos(50, 50, 1);
    v[2].setCol(0.5f, 0.5f, 0.5f, 1.0f);
    v[2].setTCor(0.0f, 0.0f);
    v[2].textID = 1.0f;


    int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    window = renderer.CreateWindow(SCR_X, SCR_Y);
    renderer.init();
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImVec4 clear_color = ImVec4(1.0f, 0.00f, 0.00f, 1.00f);
    VertexArray vao;
    vao.bind();
    ElementBuffer ebo(indices, sizeof(indices));
    VertexBuffer vbo(vertices, sizeof(vertices), 9);
    vbo.bindLayout(vao);
    glm::mat4 proj(1.0f);
    proj = glm::ortho( 0.0f, scr_x, 0.0f, scr_y, -1.0f , 200.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0,0,0));
    glm::mat4  model = glm::translate(glm::mat4(1.0f),glm::vec3(100.0f,100.0f,0));
    glm::mat4 mvp = proj * view * model;

    Shader vs(VERTEX_SHADER);
    Shader fs(FRAGMENT_SHADER);

    vs.readSourceFile("file.txt");
    fs.readSourceFile("fragment2.txt");
    ShaderProgram ps(vs.id,fs.id);
    ps.use();

    stbi_set_flip_vertically_on_load(true);

    Texture texture(GL_TEXTURE0,"container.jpg");
    Texture texture1(GL_TEXTURE1, "awesomeface.png");
    int sampler[2] = {0,1};
    ps.setUniVector("text", 2, sampler);

    ps.setUnifi("texture1",0);
    ps.setUnifi("texture2",1);
    ShaderProgram ps2(vs.id,fs.id);
    ps2.use();
    Texture wallTexture(GL_TEXTURE2, "wall.jpg");
    ps2.setUnifi("texture1", 2);
    vao.unbind();
    ebo.unbind();
    vs.deleteShader();

    float yvalue = 100;
    glm::vec3 wall = glm::vec3(100,100,0);
    glm::vec3 face = glm::vec3(300,100,0);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        {
            ps2.use();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), wall);
            glm::mat4 mvp = proj * view * model;
            ps2.setUniMat4f("aMVP", mvp);
            renderer.draw(vao, ebo, ps2);
        }/* Render here */
        {
            ps.use();
            glm::mat4 model = glm::translate(glm::mat4(1.0f),face);
            glm::mat4 mvp = proj * view * model;
            ps.setUniMat4f("aMVP", mvp);
            renderer.draw(vao, ebo, ps);
        }
        /* Poll for and process events */

        renderer.draw(vao, ebo, ps);
        glfwPollEvents();

        //imgui stuff
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            ImGui::Text("position.");               // Display some text (you can use a format strings too)
            ImGui::SliderFloat3("face", &face.x, 0.0f, 1000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::SameLine();
            ImGui::SliderFloat3("wall", &wall.x, 0.0f , 1000.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
