#ifndef CAMERA_H_
#define CAMERA_H_
#include "core/core.h"

class Camera
{
        public:
                glm::vec3 cameraPosition, cameraUp, cameraRight, cameraFront;
                float pitch, yaw, roll, lastX, lastY, fov;

                Camera();
                ~Camera();

                glm::mat4 view();
                void setWindow();
                void run(const float deltatime);
                void mouseInput(GLFWwindow* window, double xpos, double ypos);
                void SetStatus(bool camera);
                void canCameraFly(bool fly);
                void statusController();

        private:
                glm::mat4 _view;
                bool isActive;
                GLFWwindow* wind;
                bool firstmouse, canFly;
                float mouseSens, speed;

                void cameraMovement(const float deltatime);

};

#endif // CAMERA_H_
