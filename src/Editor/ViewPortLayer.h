#include "core/Layer.h"
#include "Renderer/renderer.h"
#include "Renderer/Camera2dController.h"



class ViewPortLayer : public Layer
{
public:
	ViewPortLayer() : Layer("ViewPort"), m_FrameBuffer(Renderer::GetFrameBuffer()) {}
	virtual void onUpdate(float deltatime) override;
	virtual void onImGuiRender() override;
	virtual void onEvent(Event& e) override;
private:
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
	Camera2dController camera;
	bool AreEventsEnabled = true;
	glm::vec2 m_ViewPortSize = glm::vec2(0);

};