#include "core/core.h"
#include "core/CoreFun.h"
#include "TestBatch.h"
#include "Renderer/Camera.h"
#include "core/profiling/Timer.h"
#include <filesystem>

const float SCR_X = 1920;
const float SCR_Y = 1080;

Renderer renderer(SCR_X, SCR_Y);

void processInput(GLFWwindow *window )
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

void mousecall(GLFWwindow* window, double xpos, double ypos)
{
        //camera->mouseInput(window, xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    renderer.updateResolution(width, height);
}

int main(void)
{
    Timer timer("main");
    Renderer& rend = renderer;
    float deltatime, lastframe;
    lastframe = 0.0f;
    bool prova;
    GLFWwindow* window = renderer.WindowInit();
    const char* glsl_version = "#version 430";
    renderer.init();
    renderer.ImGuiInit();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mousecall);
    stbi_set_flip_vertically_on_load(true);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    test::TestBatch tst(renderer);
    //glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        float currentframe = glfwGetTime();
        deltatime = currentframe - lastframe;
        lastframe = currentframe;

        processInput(window);
        /* Poll for and process events */
        tst.onUpdate(deltatime);
        renderer.Clear();
        tst.onRender();

        renderer.ImGuiStart();

        tst.onImGuiRender();
        renderer.ImGuiEnd();

        renderer.End();
    }
    renderer.ImGuiClose();
    glfwTerminate();
    return 0;
}
   
