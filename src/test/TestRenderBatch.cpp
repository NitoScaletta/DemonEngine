#include<TestRenderBatch.h>
#include"core/Random.h"
#include "core/Window.h"
#include "Renderer/renderer.h" 
#include "core/Input.h"
#include "core/Log.h"




namespace test{


	TestRenderBatch::TestRenderBatch()
	{
		Random::init();
		Window::SetEventCallBack(BIND_EVENT(TestRenderBatch::onEvent));
		m_quad_data.position = { 0,0,0 };
		m_quad_data.color = { 1,0,0,1 };
		
	}

	void TestRenderBatch::onUpdate(float deltatime)
	{
		camera.movement(deltatime);
		QuadData data;
		size_t x = 0, y = 0, z = 0;

		float speed = 10 * deltatime;
		if (Input::isPressed(Key::H))
			m_quad_data.position.x -= speed;
		if (Input::isPressed(Key::K))
			m_quad_data.position.x += speed;
		if (Input::isPressed(Key::U))
			m_quad_data.position.y += speed;
		if (Input::isPressed(Key::J))
			m_quad_data.position.y -= speed;

		ParticleProps props;
		props.x = camera.GetMousePositionInWorldSpceX(Input::GetMousePosition().x);
		props.y = camera.GetMousePositionInWorldSpceY(Input::GetMousePosition().y);
		props.Shape = ParticleShape::Circle;
		props.Color = { .4f, .3f, .5f, 1.0f };
		props.RotationPerTimeStep = 0;
		for (size_t i = 0; i < n_particles * Window::GetDeltaTime(); i++)
		{
			props.RandomValues();
			particles.Emit(props);
		}
		m_quad_data.position.z -1;
		m_quad_data.color = { .1f,.5f,0,zvalue };
		Renderer::DrawQuad(m_quad_data);

		m_quad_data.position = { .4f,.1,0};
		m_quad_data.color = { 0,1,1,1 };
		Renderer::DrawCircle(m_quad_data);

		m_quad_data.position = { 0,0,0};
		m_quad_data.color = { 1,1,0,1 };
		Renderer::DrawCircle(m_quad_data);

	
	}


	void TestRenderBatch::onRender()
	{
		particles.onRender();
	}


	void TestRenderBatch::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(TestRenderBatch::onMouseScrolledEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(TestRenderBatch::onMouseMovedEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(TestRenderBatch::onKeyPressedEvent));
	}


	bool TestRenderBatch::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		camera.Zoom(e.GetYoffset());
		return true;
	}

	bool TestRenderBatch::onMouseMovedEvent(MouseMovedEvent& e)
	{
		glm::vec3 position = { camera.GetMousePositionInWorldSpceX(e.GetMouseX()), camera.GetMousePositionInWorldSpceY(e.GetMouseY()), 0.0f };
		QuadData quad;
		quad.position = position;
		Renderer::DrawQuad(quad);
		return true;
	}


	bool TestRenderBatch::onKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == Key::V)
			Window::SetVSync(true);
		if (e.GetKeyCode() == Key::B)
			Window::SetVSync(false);

		return true;
	}


	void TestRenderBatch::onImGuiRender()
	{
		RendererStats stats = Renderer::GetStats();
		ImGui::Text("DrawCalls  = %d", stats.DrawCalls);
		ImGui::Text("Quads  = %d", stats.QuadIndex/4);
		ImGui::Text("Circles= %d", stats.CircleIndex/4);
		ImGui::Separator();
		ImGui::SliderInt("Particles number", &n_particles, 0, 100000);
		ImGui::SliderFloat("z value", &zvalue, -1, 1);

	}

}