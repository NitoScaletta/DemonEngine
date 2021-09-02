#ifndef TESTCUBE_H_
#define TESTCUBE_H_

#include "core.h"
#include "test.h"
#include "Camera.h"
#include "Cube.h"

namespace test {

class TestCube : public Test{
    public:
        TestCube();
        TestCube(Camera* cam);
        ~TestCube();
        Camera* camera;
        Texture texture;
        float distance;
        float move1;
        float move2;
        glm::vec3 rotation;
        std::vector<Vertex> vertices;
        glm::mat4 proj, view, model;


        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
        void passWindow(GLFWwindow* _window);
        void processInput(float deltatime);

    private:
        GLFWwindow* window;

};
    
}

#endif // TESTCUBE_H_
