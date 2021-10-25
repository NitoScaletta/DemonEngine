#ifndef __TESTBATCH_H__
#define __TESTBATCH_H__

#include <test.h>
#include <core.h>

namespace test{
class TestBatch : public Test
{
    public:
        ShaderProgram ps;
        TestBatch();
        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
    
    private:
        VertexArray vao;
        VertexBuffer vbo;
        ElementBuffer ebo;
        glm::mat4 mvp, model, proj, view;
        Shader vs, fs;
        Vertex vertices[4];
        std::vector<int> indices;
        void InitVertices();

};


}

#endif // __TESTBATCH_H__