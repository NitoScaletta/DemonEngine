#include "TestDouble.h"
#include "CoreFun.h"

namespace test{

    TestDouble::TestDouble()
    {

    }
    TestDouble::~TestDouble()
    {

    }

    TestDouble::TestDouble(GLFWwindow* wind, Camera *cam) :
        window(wind),
        camera(cam)
    {
        {
            core::createVerticesCube(vertices);
            std::vector<int> indices;
            core::CreateIndices(indices, 6);
            vao.bind();
            ebo.bind();
            ebo.set(indices.data(), indices.size()* sizeof(int));
            vbo.bindDynamic(1000);
            vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
            vao.newLayoutDynamic();
            vs.initShader(VertexType::VERTEX);
            fs.initShader(VertexType::FRAGMENT);
            vs.readSourceFile("vertex.txt");
            fs.readSourceFile("fragmentQuad.txt");
            ps.compileShader(vs.id, fs.id);
            ps.use();
            texture_1.Set("container.jpg", GL_TEXTURE0);
            texture_2.Set("wall.jpg", GL_TEXTURE1);
            texture_3.Set("awesomeface.png", GL_TEXTURE2);
            texture_1.active();
            texture_2.active();
            texture_3.active();
            ps.setUnifi("texture1", 0);
            model[0] = glm::mat4(1.0);
            model[0] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            proj = core::proj3d(4/4);
            view = camera->view();
            glm::mat4 mvp = proj * view * model[0];
            ps.setUniMat4f("aMVP", mvp);
            vao.unbind();
            vbo.unbind();
            ebo.unbind();
        }

        {
            std::vector<int> indices;
            core::CreateIndices(indices, 6);
            vertices.clear();
            vertices.push_back(Vertex(-100.0f, -2.0f, -100.0f));
            vertices.back().setTCor(0.0f, 0.0f);
            vertices.push_back(Vertex(100.0f,  -2.0f, -100.0f));
            vertices.back().setTCor(1.0f, 0.0f);
            vertices.push_back(Vertex(100.0f,  -2.0f, 100.0f));
            vertices.back().setTCor(1.0f, 1.0f);
            vertices.push_back(Vertex(-100.0f, -2.0f, 100.0f));
            vertices.back().setTCor(0.0f, 1.0f);
            vao2.bind();
            ebo2.bind();
            ebo2.set(indices.data(), indices.size()* sizeof(int));
            vbo2.bindDynamic(1000);
            vbo2.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
            vao2.newLayoutDynamic();
            vs2.initShader(VertexType::VERTEX);
            fs2.initShader(VertexType::FRAGMENT);
            vs2.readSourceFile("vertex.txt");
            fs2.readSourceFile("fragmentQuad.txt");
            ps2.compileShader(vs2.id, fs2.id);
            ps2.use();
            ps2.setUnifi("texture1", 1);
            model[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            glm::mat4 mvp = proj * view * model[0];
            ps2.setUniMat4f("aMVP", mvp);
            vao2.unbind();
            vbo2.unbind();
            ebo2.unbind();
        }
        {
            cube = new Cube[2];
            cube[0].SetPos(2, 0, 0);
            model[2] = cube[0].model();
            glm::mat4 mvp = proj * view * model[2];
            cube[0].ps.setUniMat4f("aMVP", mvp);
            cube[0].ps.setUnifi("texture1", 2);
            cube[0].unbind();
        }
        {
            cube[1].SetPos(-3, 0, 0);
            model[3] = cube[1].model();
            glm::mat4 mvp = proj * view * model[3];
            cube[1].ps.setUniMat4f("aMVP", mvp);
            cube[1].ps.setUnifi("texture1", 1);
            cube[1].unbind();
        }
    }



    void TestDouble::onUpdate(float deltatime){

        ps2.use();
        view = camera->view();
        model[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 mvp = proj * view * model[1];
        ps2.setUniMat4f("aMVP", mvp);

        model[0] = glm::rotate(model[0],glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = proj * view * model[0];
        ps.setUniMat4f("aMVP", mvp);

        model[2] = cube[0].model();
        mvp = proj * view * model[2];
        cube[0].ps.setUniMat4f("aMVP", mvp);
        cube[0].unbind();

        model[3] = cube[1].model();
        mvp = proj * view * model[3];
        cube[1].ps.setUniMat4f("aMVP", mvp);
        cube[1].unbind();
    };

    void TestDouble::onRender()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0,0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        renderer->draw(vao2, ebo2, ps2);
        renderer->draw(vao, ebo, ps);
        cube[0].draw(renderer);
        cube[1].draw(renderer);
    }

    void TestDouble::onImGuiRender()
    {}
}
