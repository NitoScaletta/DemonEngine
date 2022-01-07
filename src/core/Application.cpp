#include "core/Application.h"
#include "core/EntryPoint.h"
#include <TestRenderBatch.h>
#include "core/Window.h"
#include "core/ImGuiLayer.h"
#include "TestRenderBatch.h"



static bool demo = true;
Application *Application::s_Application;

Application::Application(const char* name)
{
    
    s_Application = this;
    Log::init();
    CrossPlatformWindow::init(name);
    Renderer::init();

    m_ImGuiLayer = new ImGuiLayer();
    m_ImGuiLayer->onAttach();

    PushLayer(new test::TestRenderBatch);

    Window::SetVSync(true);
}


void Application::run()
{
	//test::TestRenderBatch tst;
    while (!Window::ShouldClose())
    {
        Window::CalcDeltaTime();
        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->onUpdate(Window::GetDeltaTime());
        }
        //tst.onUpdate(Window::GetDeltaTime());
        Renderer::Clear();

        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->onRender();
        }
        //tst.onRender();

        m_ImGuiLayer->Begin();

        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->onImGuiRender();
        }
        ImGui::ShowDemoWindow(&demo);

        //tst.onImGuiRender();

        m_ImGuiLayer->End();

        Renderer::End();
    }
    Renderer::ImGuiClose();
    glfwTerminate();
}


