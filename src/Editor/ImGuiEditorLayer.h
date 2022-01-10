#include "core/Layer.h"


class  ImGuiEditorLayer : public Layer
{
public:
	ImGuiEditorLayer() {}
	virtual void onImGuiRender() override;
};