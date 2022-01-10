#pragma once
#include "core/Application.h"
#include "ImGuiEditorLayer.h"
#include "TestRenderBatch.h"

class EditorApp : public Application
{
	public:
		EditorApp() : Application("DemonEngin Editor")
		{
			PushTopLayer(new ImGuiEditorLayer);
			PushLayer(new TestRenderBatch);
		}

		



};


Application* CreateEditorApplication()
{
	return new EditorApp;
}
