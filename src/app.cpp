#include <core/core.h>
#include <core/CoreFun.h>
#include <TestBatch.h>
#include <TestTexture.h>
#include <core/profiling/Timer.h>
#include <filesystem>
#include <core/Window.h>
#include <core/Events/ApplicationEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/MouseEvents.h>
#include <core/Input.h>


GLFWwindow *CrossPlatformWindow::s_glfwwindow;
CrossPlatformWindow *CrossPlatformWindow::s_window = new CrossPlatformWindow;


void processInput(GLFWwindow *window )
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

int main(void)
{
    float lastframe = 0;
    Timer timer("main");
    CrossPlatformWindow::init();
    //window.SetRenderer(renderer);
    Renderer::init();
    Renderer::ImGuiInit();
    CrossPlatformWindow::SetVSync(false);

    test::TestTexture tst;
 
    while (!CrossPlatformWindow::ShouldClose())
    {
        tst.onUpdate(CrossPlatformWindow::GetDeltaTime());
        Renderer::Clear();
        tst.onRender();
        Renderer::ImGuiStart();
        tst.onImGuiRender();
        Renderer::ImGuiEnd();

        //Renderer::End();
        glfwSwapBuffers(CrossPlatformWindow::window_ptr());
        glfwPollEvents();
    }

    //Renderer::ImGuiClose();
    glfwTerminate();
    return 0;
}
   
