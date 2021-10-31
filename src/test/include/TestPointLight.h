#ifndef TESTPOINTLIGHT_H_
#define TESTPOINTLIGHT_H_

#include "core/core.h"
#include "test.h"
#include "meshes/Cube.h"
#include "meshes/Light.h"
#include "Renderer/Camera.h"


namespace test{
    class TestPointLight : public Test
    {
        public:
        Cube* cube;
        std::vector<Cube> cubes;
        int size;
        PhongLight* light;
        Plane plane;
        Texture texture1, texture2, specular1, specular2;
        Camera* camera;
        GLFWwindow* window;
        float linear, constant, quadratic;
        glm::vec3 TestDir;

        glm::mat4 proj, view;

        TestPointLight(GLFWwindow* wind, Camera* cam);
        ~TestPointLight(){};

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
    };
}


#endif // TESTDIRLIGHT_H_
