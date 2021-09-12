#include "core.h"
#include "CoreFun.h"
#include "test/TestDirLight.h"
#include "test/TestLight.h"
#include "test/TestPointLight.h"
#include "test/TestMultiLight.h"
#include "Camera.h"
#include "Timer.h"

const unsigned int SCR_X =1024;
const unsigned int SCR_Y = 768;
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
    window = renderer.CreateWindow(SCR_X, SCR_Y);
    renderer.init();
    // test::TestMultiLight tst(window, camera);
    test::TestMultiLight tst( camera, window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mousecall);
    //tst.passWindow(window);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    stbi_set_flip_vertically_on_load(true);
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
