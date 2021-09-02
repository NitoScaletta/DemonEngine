#include <iostream>
#include <vector>
#include "TestBatch.h"
#include "renderer.h"

namespace test{
    void createBuffer(int nquad, Vertex vertices[])
    {
        float x = 50.0f;
        float y = 0.0f;
        vertices[0].setPos(50.0f, 50.0f, 1.0f);
        vertices[0].setCol(1.0f, 0.0f, 0.0f, 1.0f);
        vertices[0].setTCor(1.0f, 1.0f);
        vertices[0].textID = 0.0f;
        vertices[1].setPos(150.0f, 50.0f, 1.0f);
        vertices[1].setCol(1.0f, 0.0f, 0.0f, 1.0f);
        vertices[1].setTCor(1.0f, 1.0f);
        vertices[1].textID = 0.0f;
        vertices[2].setPos(150.0f, 150.0f, 1.0f);
        vertices[2].setCol(1.0f, 0.0f, 0.0f, 1.0f);
        vertices[2].setTCor(1.0f, 1.0f);
        vertices[2].textID = 0.0f;
        vertices[3].setPos(50.0f, 150.0f, 1.0f);
        vertices[3].setCol(1.0f, 0.0f, 0.0f, 1.0f);
        vertices[3].setTCor(1.0f, 1.0f);
        vertices[3].textID = 0.0f;
        x =  250;

       for(int i = 4; i < nquad; i+=2)
       {
            vertices[i].setPos(x, y+50.0f, 1.0f);
            vertices[i].setCol(1.0f, 0.0f, 0.0f, 1.0f);
            vertices[i].setTCor(1.0f, 1.0f);
            vertices[i].textID = 0.0f;
            if(i+1 >= nquad) break;
            vertices[i+1].setPos(x, y+150.0f, 1.0f);
            vertices[i+1].setCol(1.0f, 0.0f, 0.0f, 1.0f);
            vertices[i+1].setTCor(1.0f, 1.0f);
            vertices[i+1].textID = 0.0f;
            x+=100;
       }

       for(int i = 0; i < nquad; i++)
            vertices[i].print();

    }

    void createIndices(int nquad, int indices[])
    {
        int topright = 0;
        int botright = 0;
        indices[0] = 0;
        indices[1] = 1;
        botright = indices[1];
        indices[2] = 2;
        topright = indices[2];
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;
        int i = 6;
        indices[i]=botright;
        indices[i+1] = botright+3;
        indices[i+2] = indices[i+1] + 1;
        indices[i+3] = indices[i+1] + 1;
        indices[i+4] = topright;
        indices[i+5] = botright;
        topright = topright + 3;
        botright = botright + 3;
        for(int i = 12; i < nquad; i+=6)
        {
            indices[i]=botright;
            indices[i+1] = botright+2;
            indices[i+2] = indices[i+1] + 1;
            indices[i+3] = indices[i+1] + 1;
            indices[i+4] = topright;
            indices[i+5] = botright;
            topright = topright + 2;
            botright = botright + 2;
        }
    }

    TestBatch::TestBatch(){
        const int nquad = 9;
        const int vertexnumber = 4 +(nquad-1)*2;
        int indices[nquad * 6];
        createIndices(nquad * 6, indices);
        for(int i = 0; i < nquad * 6; i++)
            std::cout << indices[i] << " ";
        std::cout << std::endl;
        Vertex vertices[vertexnumber];
        createBuffer(vertexnumber, vertices);

        vao.bind();
        ebo.bind();
        ebo.set(indices, sizeof(indices));
        vbo.bindDynamic(1000);
        vao.newLayoutDynamic();
        vbo.loadDynamic(0, sizeof(vertices), vertices);
        vs.initShader(VertexType::VERTEX);
        fs.initShader(VertexType::FRAGMENT);
        vs.readSourceFile("vertex.txt");
        fs.readSourceFile("fragment.txt");
        ps.compileShader(vs.id, fs.id);
        ps.use();
        proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f , -1.0f, 200.0f);
        ps.setUniMat4f("aMVP", proj);
    }

    TestBatch::~TestBatch(){

    }
    void TestBatch::onUpdate(float deltatime){

    }
    void TestBatch::onRender(){
        Renderer render;
        glClearColor(0,0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        render.draw(vao, ebo, ps);
    }
    void TestBatch::onImGuiRender(){

    }

}
