#include <Renderer/Camera2dController.h>
#include <core/Input.h>
#include "core/Log.h"


Camera2dController::Camera2dController() : camera(16.f/9.f), cam_pos(camera.GetPosition()) 
{
		Window::SetEventCallBack(BIND_EVENT(Camera2dController::onEvent));
}

Camera2dController::~Camera2dController() 
{

}

void Camera2dController::movement(float deltatime) 
{
	float speed = 10 * Window::GetDeltaTime();
     if(Input::isPressed(Key::W))
		cam_pos.y += speed * camera.GetZoom();
	if(Input::isPressed(Key::S))
		cam_pos.y -= speed* camera.GetZoom();
	if(Input::isPressed(Key::D))
		cam_pos.x += speed* camera.GetZoom();
	if(Input::isPressed(Key::A))
		cam_pos.x -= speed* camera.GetZoom();
	camera.SetPosition(cam_pos);
}





float Camera2dController::GetMousePositionInWorldSpceX(float mouseX) 
{
    return camera.GetPosition().x + (mouseX * CrossPlatformWindow::AspectRatio()*2 * camera.GetZoom() /
            CrossPlatformWindow::GetWidth()) - CrossPlatformWindow::AspectRatio()* camera.GetZoom();
}



float Camera2dController::GetMousePositionInWorldSpceY(float mouseY) 
{
    return camera.GetPosition().y -((mouseY * camera.GetZoom()*2 / CrossPlatformWindow::GetHeight()) - camera.GetZoom());
}



void Camera2dController::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(Camera2dController::onKeyPressedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(Camera2dController::onWindowResizeEvent));
}


bool Camera2dController::onKeyPressedEvent(KeyPressedEvent& e)
{
   	return false;

}


bool Camera2dController::onWindowResizeEvent(WindowResizeEvent& e)
{
		camera.ResetProjMatrix(e.GetWidth(), e.GetHeight());
		return false;
}

