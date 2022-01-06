#include <TestRenderBatch.h>
#include <core/profiling/Timer.h>
#include <core/Window.h>
#include <Renderer/renderer.h>
#include <core/Log.h>




int main()
{
	static bool demo = true;
    Log::init();
	DE_CORE_INFO("Welcome to DemonEngine");
    Timer timer("main");
    CrossPlatformWindow::init();
    DE_CORE_INFO("created window {}x{}", static_cast<int>(Window::GetWidth()), static_cast<int>(Window::GetHeight()));
    Renderer::init();
    Renderer::ImGuiInit();
    Window::SetVSync(true);
    test::TestRenderBatch tst;
    while (!Window::ShouldClose())
    {
        Window::CalcDeltaTime();
        tst.onUpdate(Window::GetDeltaTime());
        Renderer::Clear();
        tst.onRender();
        Renderer::ImGuiStart();
        ImGui::ShowDemoWindow(&demo);
        
        tst.onImGuiRender();
        Renderer::ImGuiRenderStats();
        Renderer::ImGuiEnd();
        Renderer::End();
    }

    Renderer::ImGuiClose();
    glfwTerminate();
    return 0;
}
   
