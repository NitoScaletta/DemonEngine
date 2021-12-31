#include <TestRenderBatch.h>
#include "core/Random.h"
#include "core/Window.h"
#include "Renderer/renderer.h" 
#include "core/Input.h"
#include "core/Log.h"
#include <string>
#include "Renderer/Colors.h"




namespace test{


	TestRenderBatch::TestRenderBatch()
	{
		Random::init();
		Window::SetEventCallBack(BIND_EVENT(TestRenderBatch::onEvent));
		m_quad_data.position = { 0,0,0 };
		m_quad_data.color = { 1,0,0,1 };
		t_slot = 0;
		HappyFace = Texture("awesomeface.png");
		Wall = Texture("wall.jpg");
		Background = Texture("bg.jpg");
	}

	void TestRenderBatch::onUpdate(float deltatime)
	{
		Renderer::DrawTexturedQuad({0,0,-.9f}, Background, 100.0f, 0.0f, 1000.0f);
		camera.movement(deltatime);
		QuadData data;
		float x = 0, y = 0, z = 0;

		
		ParticleProps props;
		props.Position = { camera.GetMousePositionInWorldSpceX(Input::GetMousePosition().x), camera.GetMousePositionInWorldSpceY(Input::GetMousePosition().y), .6f };
		props.Shape = ParticleShape::Circle;
		props.Color = { .4f, .3f, .5f, 1.0f };
		props.RotationPerTimeStep = 0;
		for (size_t i = 0; i < n_particles * deltatime; i++)
		{
			props.RandomValues();
			particles.Emit(props);
		}

		for (size_t i = 0; i <= t_slot; i++)
		{

			m_quad_data.position = glm::vec3(x, y, 0);
			Renderer::DrawTexturedQuad(m_quad_data.position, Wall, 1.0f, -1 * Rotation, 10);
			//Renderer::DrawQuad(m_quad_data.position, 0, { .5f,.5f,1.0f }, Color::White);
			if ((i % 50 == 0)&&(i!=0))
			{
				x = 0;
				y+=.5f;
			}
			else
				x+=.5f;
		}
		m_quad_data.position = glm::vec3(0, 0, 0.7f);

		Renderer::DrawTexturedQuad({ 0,0,.3f }, HappyFace, 1.0f, Rotation++);
		
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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(TestRenderBatch::onWindowResizeEvent));
	}


	bool TestRenderBatch::onMouseScrolledEvent(MouseScrolledEvent& e)
	{
		camera.Zoom(e.GetYoffset());
		return true;
	}

	bool TestRenderBatch::onMouseMovedEvent(MouseMovedEvent& e)
	{
		glm::vec3 position = { camera.GetMousePositionInWorldSpceX(e.GetMouseX()), camera.GetMousePositionInWorldSpceY(e.GetMouseY()), 0.0f };
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
		ImGui::Separator();
		ImGui::Text("DrawCalls  = %d", stats.DrawCalls);
		ImGui::Text("Quads		= %d", stats.QuadIndex/4);
		ImGui::Text("Circles	= %d", stats.CircleIndex/4);
		ImGui::Separator();
		ImGui::SliderInt("Particles number", &n_particles, 0, 100000);
		ImGui::SliderInt("TextureSlot", &t_slot, 0, 10000);

	}

	bool TestRenderBatch::onWindowResizeEvent(WindowResizeEvent& e)
	{
		camera.ResetAspectRatio(e.GetWidth(), e.GetHeight());
		return true;
	}
	

}