#ifndef __TESTBATCH_H__
#define __TESTBATCH_H__

#include <test.h>
#include <core/core.h>
#include <Renderer/Camera2d.h>

namespace test{
class TestBatch : public Test
{
    public:
        TestBatch(Renderer& render);
        ShaderProgram ps;
        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
        

    
    private:
        GLFWwindow* window;
        Renderer& renderer;
        VertexArray vao;
        int x = 0;
        VertexBuffer vbo;
        ElementBuffer ebo;
        glm::mat4 mvp, model, proj, view;
        glm::vec3 cam_pos = {0, 0, 0};
        Shader vs, fs;
        int nquad, prev_nquad;
        Vertex *vertices;
        std::vector<Vertex> verts;
        std::vector<int> indices;
        void InitVertices(int nquad);
        void VerticesInit(int nquad);
        void VerticesInitParallel(int nquad);
        void CameraController(float deltatime);

};



void multiloop(Vertex* vertices, int i, int x, int y, int n);

}

#endif // __TESTBATCH_H__