#include <TestRenderBatch.h>
#include <core/profiling/Timer.h>
#include <core/Window.h>
#include <Renderer/renderer.h>
#include <core/Log.h>




int main(void)
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
        Renderer::Clear();
        tst.onUpdate(Window::GetDeltaTime());
        tst.onRender();
		Renderer::RenderAll();
        Renderer::ImGuiStart();
        ImGui::ShowDemoWindow(&demo);
        tst.onImGuiRender();
        Renderer::ImGuiEnd();
        Renderer::End();
    }

    Renderer::ImGuiClose();
    glfwTerminate();
    return 0;
}
   
