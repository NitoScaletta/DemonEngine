#include <Renderer/Camera2dController.h>
#include <core/Input.h>


Camera2dController::Camera2dController() : camera(16.f/9.f), cam_pos(camera.GetPosition()) 
{
}

Camera2dController::~Camera2dController() 
{

}

void Camera2dController::movement(float deltatime) 
{
        float speed = 10*deltatime;
        if(Input::isPressed(Key::W))
            cam_pos.y += speed;
        if(Input::isPressed(Key::S))
            cam_pos.y -= speed;
        if(Input::isPressed(Key::D))
            cam_pos.x += speed;
        if(Input::isPressed(Key::A))
            cam_pos.x -= speed;
        camera.SetPosition(cam_pos);
}





float Camera2dController::GetMousePositionInWorldSpceX(float mouseX) 
{
    return camera.GetPosition().x + (mouseX * CrossPlatformWindow::AspectRatio()*2 / 
            CrossPlatformWindow::GetWidth()) - CrossPlatformWindow::AspectRatio();
}



float Camera2dController::GetMousePositionInWorldSpceY(float mouseY) 
{
    return camera.GetPosition().y -((mouseY * camera.GetZoom()*2 / CrossPlatformWindow::GetHeight()) - camera.GetZoom());
}


