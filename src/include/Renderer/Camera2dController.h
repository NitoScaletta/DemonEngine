#ifndef __CAMERA2DCONTROLLER_H__
#define __CAMERA2DCONTROLLER_H__

#include <Renderer/Camera2d.h>
#include <core/Events/Events.h>


class Camera2dController
{
    public:
    Camera2dController();
    ~Camera2dController();

    void movement(float deltatime);
    glm::mat4 GetViewProjMatrix()           { return camera.GetViewProjMatrix(); }
    void ResetAspectRatio(float x, float y) { camera.ResetProjMatrix(x/y); }
    void rotate(){ }
    void Zoom(float zoom)                   { camera.ChangeZoomLevel(zoom);}
    float GetZoom()                         { return camera.GetZoom(); }
    float GetMousePositionInWorldSpceX(float mouseX);
    float GetMousePositionInWorldSpceY(float mouseY);


    private:
    Camera2d camera;
    glm::vec3 cam_pos;
    float rotation;
};





#endif // __CAMERA2DCONTROLLER_H__