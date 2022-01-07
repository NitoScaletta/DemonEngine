#include "core/Application.h"
#include "core/EntryPoint.h"
#include <TestRenderBatch.h>
#include "core/Window.h"


static bool demo = true;
Application *Application::s_Application;

Application::Application(const char* name)
{
    
    s_Application = this;
    Log::init();
    CrossPlatformWindow::init(name);
    Renderer::init();
    Renderer::ImGuiInit();
    Window::SetVSync(true);
}


void Application::run()
{
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
}


