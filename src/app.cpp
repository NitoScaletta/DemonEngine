#include <TestSpawnQuad.h>
#include <core/profiling/Timer.h>
#include <core/Window.h>
#include <Renderer/renderer.h>





int main(void)
{
    Timer timer("main");
    CrossPlatformWindow::init();
    Renderer::init();
    Renderer::ImGuiInit();
   Window::SetVSync(true);

    test::TestSpawQuad tst;
 
    while (!Window::ShouldClose())
    {
        Window::CalcDeltaTime();
        tst.onUpdate(Window::GetDeltaTime());
        Renderer::Clear();
        tst.onRender();
        Renderer::ImGuiStart();
        tst.onImGuiRender();
        Renderer::ImGuiEnd();

        //Renderer::End();
        glfwSwapBuffers(Window::window_ptr());
        glfwPollEvents();
    }

    //Renderer::ImGuiClose();
    glfwTerminate();
    return 0;
}
   
