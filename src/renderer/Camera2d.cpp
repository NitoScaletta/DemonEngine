#include <Renderer/Camera2d.h>
Camera2d::Camera2d(float aspectratio) :
ProjMatrix(glm::ortho(-aspectratio * ZoomLevel, aspectratio*ZoomLevel, -ZoomLevel, ZoomLevel, -1.0f, 10.0f)), 
ViewMatrix(glm::mat4(1.0f)), Position(glm::vec3(0.0f)), Rotation(0.0f),
AspectRatio(aspectratio)
{
    ViewProjMatrix = ProjMatrix * ViewMatrix;
}

void Camera2d::CalcViewProjMatrix() 
{
    ViewMatrix = glm::translate(glm::mat4(1.0f), Position)
    * glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), {0.0f, 0.0f, 1.0f});

    ViewMatrix = glm::inverse(ViewMatrix);
    ViewProjMatrix = ProjMatrix * ViewMatrix;
}
