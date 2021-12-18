#include <TestSpawnQuad.h>
#include <TestRenderBatch.h>
#include <core/profiling/Timer.h>
#include <core/Window.h>
#include <Renderer/renderer.h>
#include <core/Log.h>




int main(void)
{

    Log::init();
	DE_CORE_INFO("Welcome to DemonEngine");
    Timer timer("main");
    CrossPlatformWindow::init();
    Renderer::init();
    Renderer::ImGuiInit();
    Window::SetVSync(true);
    test::TestRenderBatch tst;
    while (!Window::ShouldClose())
    {
        Window::CalcDeltaTime();
        Renderer::Clear();
        tst.onUpdate(Window::GetDeltaTime());
        tst.onRender();
		Renderer::RenderAll();
        Renderer::ImGuiStart();
        tst.onImGuiRender();
        Renderer::ImGuiEnd();
        Renderer::End();
    }

    Renderer::ImGuiClose();
    glfwTerminate();
    return 0;
}
   
