#pragma once
#include "core/Layer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "core/Events/KeyEvents.h"
#include "Renderer/Camera2dController.h"

class ImGuiLayer : public Layer {
public:
	ImGuiLayer() : Layer("ImGui Layer") {}
	~ImGuiLayer() {}

	virtual void onAttach() override;
	virtual void Begin();
	virtual void onEvent(Event& e) override;
	virtual bool onKeyPressedEvent(KeyPressedEvent& e);
	virtual void End();
};


