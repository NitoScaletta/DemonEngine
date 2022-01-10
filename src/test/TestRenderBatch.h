#ifndef __TESTRENDERBATCH__
#define __TESTRENDERBATCH__

#include "core/Log.h"
#include "Renderer/Camera2dController.h"
#include "Renderer/ParticleSystem.h"
#include "core/Events/MouseEvents.h"
#include "core/Events/KeyEvents.h"
#include "core/Events/ApplicationEvents.h"
#include "Renderer/FrameBuffer.h"
#include "core/Layer.h"


class TestRenderBatch : public Layer
{
public: 
	TestRenderBatch();
	~TestRenderBatch() { }
	void onUpdate(float deltatime) override;
	void onRender() override;
	void onImGuiRender() override;
	void onEvent(Event& e) override;
	bool onMouseScrolledEvent(MouseScrolledEvent& e);
	bool onMouseMovedEvent(MouseMovedEvent& e);
	bool onKeyPressedEvent(KeyPressedEvent& e);
	bool onWindowResizeEvent(WindowResizeEvent& e);

private:

		
	int32_t quadindex;
	QuadData m_quad_data;
	std::shared_ptr<ParticleSystem> particles;
	int n_particles = 1000;
	std::shared_ptr<Texture> Numbers[40], HappyFace, Wall, Background, anim, container;
	std::shared_ptr<SubTexture> Tile;
	std::shared_ptr<FrameBuffer> fBuffer;
	float Rotation=0;
	int t_slot;
	glm::vec2 m_ViewPortSize;
    bool AreEventsEnabled = true;

	Camera2dController camera;
		
	

};



#endif