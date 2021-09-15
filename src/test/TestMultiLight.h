#pragma once 
#include "test.h"
#include "Camera.h"
#include "core.h"
#include "Cube.h"
#include "CoreFun.h"
#include "Light.h"
#include <vector>


namespace test
{
    class TestMultiLight : public Test 
    {
        public:
        TestMultiLight(Camera* cam, GLFWwindow * window);
        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;

        Cube* cube;
        Plane* plane;
        DirectionalLight* dirlight;
        std::vector<PointLight> pointlight;
        glm::vec3 light_position[10];
        
        glm::mat4 proj, view;
        int n_pointlight;
        Camera* camera;

    };
}