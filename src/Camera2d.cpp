#include <Camera2d.h>
Camera2d::Camera2d(float left, float right, float bottom, float top) :
ProjMatrix(glm::ortho(left, right, bottom, top, -1.0f, 200.0f)), ViewMatrix(glm::mat4(1.0f)), Position(glm::vec3(0.0f)), Rotation(0.0f)
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
