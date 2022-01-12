#pragma once
#include "core/Application.h"
#include "ImGuiEditorLayer.h"
#include "TestRenderBatch.h"
#include "ViewPortLayer.h"

class EditorApp : public Application
{
	public:
		EditorApp() : Application("DemonEngin Editor")
		{
			PushTopLayer(new ViewPortLayer);
			PushTopLayer(new ImGuiEditorLayer);
			PushLayer(new TestRenderBatch);
			m_LayerStack.PrintLayerStackList();

		}

		



};


Application* CreateEditorApplication()
{
	return new EditorApp;
}
