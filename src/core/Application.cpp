#include "core/Application.h"
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

	Window::SetEventCallBack(BIND_EVENT(Application::onEvent));
    m_ImGuiLayer = new ImGuiLayer();
    PushTopLayer(m_ImGuiLayer);


    Window::SetVSync(true);
}


void Application::run()
{
	//test::TestRenderBatch tst;
    while (!Window::ShouldClose())
    {
        float deltatime = Window::CalcDeltaTime();
        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->onUpdate(deltatime);
        }

        Renderer::Clear();

        for (auto& layer : m_LayerStack.GetStack())
        {
            layer->onRender();
        }

        m_ImGuiLayer->Begin();

        int32_t size = m_LayerStack.GetStack().size() - 1;
        for ( int i = size; i>=0;  i--)
        {
            m_LayerStack.GetStack()[i]->onImGuiRender();

        }

        ImGui::ShowDemoWindow(&demo);

        Renderer::ImGuiRenderStats();

        m_ImGuiLayer->End();

        Renderer::End();
    }
    Renderer::ImGuiClose();
    glfwTerminate();
}



void Application::onEvent(Event& e)
{
    int32_t size = m_LayerStack.GetStack().size() - 1;
    
    for ( int i = size; i>=0;  i--)
    {
        m_LayerStack.GetStack()[i]->onEvent(e);

    }
}

