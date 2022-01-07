#pragma once
#include "core/Events/ApplicationEvents.h"


class Application
{
public:
	Application(const char* name);
	~Application() {}
	void onUpdate() {}
	void onEvent(Event& e) {}
	void run();
private:
	void onWindowResized(WindowResizeEvent& e) {}
	void onWindowClose(WindowCloseEvent& e) {}
	static Application *s_Application;
};