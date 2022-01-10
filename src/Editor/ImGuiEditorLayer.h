#include "core/Layer.h"


class  ImGuiEditorLayer : public Layer
{
public:
	ImGuiEditorLayer() : Layer("ImGuiEditorLayer") {}
	virtual void onImGuiRender() override;
};