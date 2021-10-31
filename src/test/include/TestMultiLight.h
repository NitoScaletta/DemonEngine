#pragma once 
#include "test.h"
#include "Renderer/Camera.h"
#include "core/core.h"
#include "meshes/Cube.h"
#include "core/CoreFun.h"
#include "meshes/Light.h"
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

        std::vector<Cube> cubes;
        Cube* cube;
        Plane* plane;
        DirectionalLight* dirlight;
        std::vector<PointLight> pointlight;
        Flashlight* flashlight;
        glm::vec3 light_position[10];
        
        glm::mat4 proj, view;
        int n_pointlight;
        Camera* camera;

    };
}