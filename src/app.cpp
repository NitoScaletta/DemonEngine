#include <core/core.h>
#include <core/CoreFun.h>
#include <TestBatch.h>
#include <TestTexture.h>
#include <TestSpawnQuad.h>
#include <core/profiling/Timer.h>
#include <filesystem>
#include <core/Window.h>
#include <core/Events/ApplicationEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/MouseEvents.h>
#include <core/Input.h>





int main(void)
{
    Timer timer("main");
    CrossPlatformWindow::init();
    Renderer::init();
    Renderer::ImGuiInit();
    CrossPlatformWindow::SetVSync(true);

    test::TestSpawQuad tst;
 
    while (!CrossPlatformWindow::ShouldClose())
    {
        CrossPlatformWindow::CalcDeltaTime();
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
   
