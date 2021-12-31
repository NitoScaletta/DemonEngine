#ifndef __TESTRENDERBATCH__
#define __TESTRENDERBATCH__

#include "test.h"
#include "Renderer/Camera2dController.h"
#include "Renderer/ParticleSystem.h"
#include "core/Events/MouseEvents.h"
#include "core/Events/KeyEvents.h"
#include "core/Events/ApplicationEvents.h"
namespace test {


	class TestRenderBatch : public Test
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
		ParticleSystem particles;
		int n_particles = 1000;
		Texture Numbers[40], HappyFace, Wall, Background;
		float Rotation=0;
		int t_slot;



		Camera2dController camera;
		
	

	};



}
#endif