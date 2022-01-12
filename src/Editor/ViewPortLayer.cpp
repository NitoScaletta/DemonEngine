#include "ViewPortLayer.h"



void ViewPortLayer::onImGuiRender()
{  
	ImGui::Begin("viewport");
	glm::vec2 viewportsize = { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y };
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows)|| ImGui::IsWindowHovered())
	{
		AreEventsEnabled = true;
		camera.EnableEvents(true);
	}
	else
	{
		AreEventsEnabled = false;
		camera.EnableEvents(false);
	}

	if (m_ViewPortSize != viewportsize)
	{
		FrameBufferProps fbprops;
		fbprops.width = viewportsize.x;
		fbprops.height = viewportsize.y;
		m_ViewPortSize = viewportsize;
		glViewport(0,0,m_ViewPortSize.x, m_ViewPortSize.y);
		m_FrameBuffer->Resize(fbprops);
		camera.ResetAspectRatio(m_ViewPortSize.x, m_ViewPortSize.y);
	}
    uint32_t Buffer = m_FrameBuffer->GetColorAttachmentId();
    ImGui::Image((void*)Buffer, { m_ViewPortSize.x, m_ViewPortSize.y},ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    ImGui::End();

}


void ViewPortLayer::onUpdate(float deltatime)
{
	camera.movement(deltatime);
}


void ViewPortLayer::onEvent(Event& e)
{

}