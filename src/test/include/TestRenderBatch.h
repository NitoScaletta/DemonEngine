#ifndef __TESTRENDERBATCH__
#define __TESTRENDERBATCH__

#include "test.h"
#include "Renderer/Camera2dController.h"
#include "Renderer/ParticleSystem.h"
#include "core/Events/MouseEvents.h"
#include "core/Events/KeyEvents.h"
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

	private:

		
		int32_t quadindex;
		QuadData m_quad_data;
		ParticleSystem particles;
		int n_particles = 1000;
		float zvalue=0;



		Camera2dController camera;
		
	

	};



}
#endif