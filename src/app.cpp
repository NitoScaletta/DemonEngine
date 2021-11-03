#include <core/core.h>
#include <core/CoreFun.h>
#include <TestBatch.h>
#include <core/profiling/Timer.h>
#include <filesystem>
#include <core/Window.h>
#include <core/Events/ApplicationEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/MouseEvents.h>


Renderer renderer(1280.f, 720.f);

void processInput(GLFWwindow *window )
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

int main(void)
{
    float lastframe = 0;
    Timer timer("main");
    CrossPlatformWindow window(renderer);
    window.init();
    //window.SetRenderer(renderer);
    renderer.SetWindow(window.ptrWindow());
    renderer.ImGuiInit();
    renderer.init();
    window.SetVSync(true);


    test::TestBatch tst(renderer, window);
 
    while (!window.ShouldClose())
    {
        tst.onUpdate(window.GetDeltaTime());
        renderer.Clear();
        tst.onRender();
        renderer.ImGuiStart();
        tst.onImGuiRender();
        renderer.ImGuiEnd();

        //renderer.End();
        glfwSwapBuffers(window.ptrWindow());
        glfwPollEvents();
    }

    //renderer.ImGuiClose();
    glfwTerminate();
    return 0;
}
   
