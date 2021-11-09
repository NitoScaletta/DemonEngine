#ifndef TESTQUAD_H_
#define TESTQUAD_H_

#include "../include/test.h"
#include "../include/Renderer/Shader.h"
#include "Renderer/glObjects.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLFW/glfw3.h"

namespace test{

class TestQuad : public Test
{
    public:
        Texture texture;
        glm::mat4 proj, view, model, mvp;
        glm::vec3 move;
        glm::vec3 movecamera;
        glm::vec3 quad_scale;
        float quad_rotation;


        TestQuad();
        ~TestQuad();

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
        void passWindow(GLFWwindow* windowptr);


    private:
        GLFWwindow* window;
        void processInput();
};

}


#endif // TESTQUAD_H_
