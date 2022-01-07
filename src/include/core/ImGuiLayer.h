#pragma once
#include "core/Layer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class ImGuiLayer : public Layer {
public:
	ImGuiLayer() : Layer("ImGui Layer") {}
	~ImGuiLayer() {}

	virtual void onAttach() override;
	virtual void Begin();
	virtual void End();
};