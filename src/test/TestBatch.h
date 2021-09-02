#ifndef TESTBATCH_H_
#define TESTBATCH_H_
#include "GLFW/glfw3.h"
#include "test.h"
#include "Shader.h"
#include "glObjects.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace test{
    class TestBatch : public Test{
        public:
            glm::mat4 proj,model,view;
            glm::vec3 move;


            TestBatch();
            ~TestBatch();
            void onUpdate(float deltatime) override;
            void onRender() override;
            void onImGuiRender() override;


    };
}


#endif // TESTBATCH_H_
