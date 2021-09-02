#ifndef TESTDOUBLE_H_
#define TESTDOUBLE_H_

#include "test.h"
#include "core.h"
#include "Camera.h"
#include "Cube.h"

namespace test{

    class TestDouble : public Test{
            public:
                std::vector<Vertex> vertices;
                VertexArray vao2;
                ElementBuffer ebo2;
                VertexBuffer vbo2;
                Shader vs2, fs2;
                ShaderProgram ps2;
                Texture texture_1, texture_2, texture_3;
                GLFWwindow* window;
                Camera* camera;
                Cube* cube;

                glm::mat4 proj, view, model[5];



                TestDouble();
                TestDouble(GLFWwindow* wind, Camera* cam);
                ~TestDouble();
                void onUpdate(float deltatime) override;
                void onRender() override;
                void onImGuiRender() override;
    };
}


#endif // TESTDOUBLE_H_
