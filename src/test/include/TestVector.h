#ifndef TESTVECTOR_H_
#define TESTVECTOR_H_
#include "../include/test.h"
#include "../glad/glad.h"
#include "../include/graphic/glObjects.h"
#include "../include/graphic/Shader.h"
#include <vector>


namespace test{
    class TestVector : public Test{
        public:
            glm::mat4 proj,model,view;
            glm::vec3 move;
            std::vector<Vertex> vertices;
            std::vector<int> indices;
            int nquad;
            int p_nquad;


             TestVector();
            ~TestVector();
            void onUpdate(float deltatime) override;
            void onRender() override;
            void onImGuiRender() override;

    };

}



#endif // TESTVECTOR_H_
