#pragma once 
#include "test.h"
#include "Camera.h"
#include "core.h"
#include "Cube.h"
#include "CoreFun.h"


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
        glm::mat4 proj, view;
        Camera* camera;

    };
}