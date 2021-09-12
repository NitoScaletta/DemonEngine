#ifndef TESTDIRLIGHT_H_
#define TESTDIRLIGHT_H_

#include "core.h"
#include "test.h"
#include "Cube.h"
#include "Light.h"
#include "Camera.h"
#include <future>



namespace test{
    class TestDirLight : public Test
    {
        public:
        std::vector<Cube> cubes;
        int size;
        Flashlight* light;
        Plane plane;
        Texture texture1, texture2, specular1, specular2;
        Camera* camera;
        GLFWwindow* window;
        float linear, constant, quadratic;
        glm::vec3 TestDir;
        TextureData data[4];

        std::vector<std::future<void>> t_futures;

        glm::mat4 proj, view;

        TestDirLight(GLFWwindow* wind, Camera* cam);
        ~TestDirLight(){};

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
    };
}


#endif // TESTDIRLIGHT_H_
