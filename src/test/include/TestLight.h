#ifndef TESTLIGHT_H_
#define TESTLIGHT_H_
#include "core/core.h"
#include "test.h"
#include "Renderer/Camera.h"
#include "meshes/Cube.h"
#include "meshes/Light.h"


namespace test {

    class TestLight : public Test
    {
        public:
            TestLight(GLFWwindow* wind, Camera* cam);
            void onUpdate(float deltatime) override;
            void onRender() override;
            void onImGuiRender() override;

        private:
            float rvalue;
            float AmbientLight;
            std::vector<Vertex> vertices;
            glm::mat4 proj, view, *model, lightModel;
            Cube* cube;
            PhongLight* light;
            Plane* plane;
            Camera* camera;
            Texture texture1, texture2, specular1, specular2;
            GLFWwindow* window;
            int s;

    };
}


#endif // TESTLIGHT_H_
