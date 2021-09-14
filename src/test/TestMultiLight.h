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
        
        glm::mat4 proj, view;
        float vec[3] = {0,0,0};
        int n_pointlight;
        Camera* camera;

    };
}