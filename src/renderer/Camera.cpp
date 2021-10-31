#include <Renderer/Camera.h>
#include <core/CoreFun.h>

Camera::~Camera(){}
Camera::Camera() :
                cameraPosition(glm::vec3(0.0f, 0.0f, 3.0f)),
                cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
                cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
                yaw(90.0f),
                pitch(0.0f),
                fov(45.0f),
                lastX(1024/2),
                lastY(768/2),
                isActive(true),
                firstmouse(true),
                mouseSens(0.07f),
                wind(nullptr),
                speed(10.0f),
                canFly(true)
{
}



void Camera::run(const float deltatime)
{
    cameraMovement(deltatime);
}


glm::mat4 Camera::view()
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::mouseInput(GLFWwindow* window, double xpos, double ypos)
{
    wind = window;
    if(isActive)
    {
        if(firstmouse)
        {
            wind = window;
            lastX = xpos;
            lastY = ypos;
            firstmouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;
        lastX = xpos;
        lastY = ypos;
        xoffset *= mouseSens;
        yoffset *= mouseSens;

        yaw += xoffset;
        pitch -= yoffset;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
        cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
    }
}


void Camera::cameraMovement(const float deltatime)
{
    if(isActive){
        if(wind != nullptr){
            if(glfwGetKey(wind, GLFW_KEY_W) == GLFW_PRESS)
                cameraPosition += cameraFront * speed * deltatime;
            if(glfwGetKey(wind, GLFW_KEY_S) == GLFW_PRESS)
                cameraPosition -= cameraFront * speed * deltatime;
            if(glfwGetKey(wind, GLFW_KEY_D) == GLFW_PRESS)
                cameraPosition += cameraRight * speed * deltatime;
            if(glfwGetKey(wind, GLFW_KEY_A) == GLFW_PRESS)
                cameraPosition -= cameraRight * speed * deltatime;
            if(!canFly)
                cameraPosition.y = 0.0f;
        }
    }
}

void Camera::canCameraFly(bool fly)
{
   canFly = fly;
}

void Camera::SetStatus(bool status)
{
   isActive = status;
}


void Camera::statusController()
{
    if(wind != nullptr){
        if(glfwGetKey(wind, GLFW_KEY_P) == GLFW_PRESS)
            SetStatus(true);
        if(glfwGetKey(wind, GLFW_KEY_O) == GLFW_PRESS)
            SetStatus(false);
    }
}
