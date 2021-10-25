#include "core.h"
#include "CoreFun.h"
#include "TestBatch.h"
#include "Camera.h"
#include "Timer.h"
#include <filesystem>

const unsigned int SCR_X = 1000;
const unsigned int SCR_Y = 1000;
const float scr_x = SCR_X;
const float scr_y = SCR_Y;
Camera* camera = new Camera();

void processInput(GLFWwindow *window )
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

void mousecall(GLFWwindow* window, double xpos, double ypos);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    Timer timer("main");
    float deltatime, lastframe;
    lastframe = 0.0f;
    bool prova;
    Renderer renderer;
    GLFWwindow* window;
    const char* glsl_version = "#version 430";
    if (!glfwInit())
    {
        std::cout << "errore" << std::endl;
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_X, SCR_Y, "DemonEngine", NULL, NULL);
    if (!window)
    {
        std::cout << "Impossibile creare finestra glfw" << std::endl;
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    renderer.init();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mousecall);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    stbi_set_flip_vertically_on_load(true);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    test::TestBatch tst;
    //glEnable(GL_DEPTH_TEST);
    renderer.wind = window;
    while (!glfwWindowShouldClose(window))
    {
        renderer.update();
        float currentframe = glfwGetTime();
        deltatime = currentframe - lastframe;
        lastframe = currentframe;

        camera->run(deltatime);
        processInput(window);
        /* Poll for and process events */
        tst.onUpdate(deltatime);
        tst.onRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        tst.onImGuiRender();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                            1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    delete(camera);
    return 0;
}
    void mousecall(GLFWwindow* window, double xpos, double ypos)
    {
        camera->mouseInput(window, xpos, ypos);
    }
