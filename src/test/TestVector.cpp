#include "TestVector.h"
#include "core/CoreFun.h"
#include "core/core.h"


namespace test {

TestVector::TestVector() : nquad(1)
{
    p_nquad = nquad;
    core::createBuffer(4, vertices, 50, 50, 100, 100);
    core::createIndices(nquad*6, indices);
    std::cout << sizeof(Vertex) * 5 << " kilobytes" << '\n';
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(),sizeof(int)*indices.size());
    vbo.bindDynamic(5000);
    vao.newLayoutDynamic();
    vbo.loadDynamic(0,sizeof(Vertex)*vertices.size(), vertices.data());
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile("fragment.txt");
    ps.compileShader(vs.id, fs.id);
    ps.use();
    proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f , -1.0f, 200.0f);

}
    TestVector::~TestVector(){}

void TestVector::onUpdate(float deltatime){
        ps.use();
        ps.setUniMat4f("aMVP", proj);
        int vertexnumber = 4 + (nquad -1) * 2;
        if(nquad != p_nquad){
            core::ClearScreen();
            core::createBuffer(vertexnumber, vertices, 50, 50);
            core::createIndices(nquad*6, indices);
            vbo.loadDynamic(0,sizeof(Vertex)*vertices.size(), vertices.data());
            ebo.set(indices.data(),sizeof(int)*indices.size());
        }
        p_nquad = nquad;

    }


    void TestVector::onRender(){
        Renderer render;
        glClearColor(0,0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        render.draw(vao, ebo, ps);
    }
    void TestVector::onImGuiRender(){
        ImGui::SliderInt("quad number",&nquad, 0, 30);
    }
}
