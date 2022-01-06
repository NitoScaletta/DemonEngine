#ifndef __CAMERA2DCONTROLLER_H__
#define __CAMERA2DCONTROLLER_H__

#include <Renderer/Camera2d.h>
#include <core/Events/Events.h>
#include <core/Events/ApplicationEvents.h>


class Camera2dController
{
    public:
    Camera2dController();
    ~Camera2dController();

    void movement(float deltatime);
    const glm::mat4& GetViewProjMatrix() const           { return camera.GetViewProjMatrix(); }
    void ResetAspectRatio(float x, float y)              { camera.ResetProjMatrix(x/y); }
    void rotate(){ }
    void Zoom(float zoom)                                { camera.ChangeZoomLevel(zoom);}
    const float& GetZoom() const                         { return camera.GetZoom(); }
    float GetMousePositionInWorldSpceX(float mouseX);
    float GetMousePositionInWorldSpceY(float mouseY);


    private:
    Camera2d camera;
    glm::vec3 cam_pos;
    float rotation;

    void onEvent(Event& e);
    bool onKeyPressedEvent(KeyPressedEvent& e);
	bool onWindowResizeEvent(WindowResizeEvent& e);
};





#endif // __CAMERA2DCONTROLLER_H__