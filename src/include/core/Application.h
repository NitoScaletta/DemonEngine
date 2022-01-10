#pragma once
#include "core/Events/ApplicationEvents.h"
#include "core/Layer.h"
#include "core/ImGuiLayer.h"


class Application
{
public:
	Application(const char* name);
	~Application() {}
	void onUpdate() {}
	void onEvent(Event& e);
	void run();
	void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }
	void PushTopLayer(Layer* layer) { m_LayerStack.PushTopLayer(layer); }
	//static Application* Get() { return s_Application; }


protected:
	void onWindowResized(WindowResizeEvent& e) {}
	void onWindowClose(WindowCloseEvent& e) {}
	static Application *s_Application;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;
};