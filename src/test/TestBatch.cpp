#include "include/TestBatch.h"
#include "CoreFun.h"


namespace test{
    TestBatch::TestBatch(){

        InitVertices();
        vao.bind();
        ebo.bind();
        ebo.set(indices.data(), sizeof(int)*indices.size());
        vbo.bindDynamic(1000);
        vbo.loadDynamic(0,sizeof(Vertex)*4,vertices);
        vao.newLayoutDynamic();
        vs.initShader(VertexType::VERTEX);
        fs.initShader(VertexType::FRAGMENT);
        vs.readSourceFile("VertexQuad.glsl");
        fs.readSourceFile("fragment.glsl");
        ps.compileShader(vs.id,fs.id);
        ps.use();
        proj = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, -2.0f, 200.0f);
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        mvp = proj * view * model;
        ps.setUniMat4f("aMVP", mvp);
    }



    void TestBatch::onUpdate(float deltatime) 
    {
    }

    void TestBatch::onRender() 
    {
        Renderer renderer;
        glClearColor(0.6f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.draw(vao,ebo, ps);
    }


    void TestBatch::onImGuiRender() 
    {

    }

    void TestBatch::InitVertices()
    {
        vertices[0].setPos(-100,-100);
        vertices[1].setPos( 100,-100);
        vertices[2].setPos( 100, 100);
        vertices[3].setPos(-100, 100);
        core::CreateIndices(indices, 1, true);
    }
}