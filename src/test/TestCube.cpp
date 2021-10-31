#include "TestCube.h"
#include "core/CoreFun.h"

namespace test{
    TestCube::TestCube(){}

    TestCube::TestCube(Camera* cam) : distance(-5.0f),
                           rotation(glm::vec3(0.0f)),
                           model(glm::mat4(1.0f)),
                           view(glm::mat4(1.0f)),
                           camera(cam)
    {
        std::vector<int> indici;
        core::CreateIndices(indici, 7);
        core::createVerticesCube(vertices);
        vao.bind();
        ebo.bind();
        ebo.set(indici.data(), sizeof(int)*indici.size());
        vbo.bindDynamic(1000);
        vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(),vertices.data());
        vao.newLayoutDynamic();
        vs.initShader(VertexType::VERTEX);
        fs.initShader(VertexType::FRAGMENT);
        vs.readSourceFile("vertex.txt");
        fs.readSourceFile("fragmentQuad.txt");
        ps.compileShader(vs.id, fs.id);
        ps.use();
        texture.Set("container.jpg", GL_TEXTURE0);
        ps.setUnifi("texture1",0);
        proj = core::proj3d(4.0f/3.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 mvp = proj * view * model;
        ps.setUniMat4f("aMVP", mvp);
        vao.unbind();
        ebo.unbind();
        vbo.unbind();
    }


    TestCube::~TestCube()
    {

    }

    void TestCube::onUpdate(float deltatime)
    {
        processInput(deltatime);
        if(move1 != move2)
            model = glm::translate(model, glm::vec3(move1, 0.0f, 0.0f));
        model = glm::rotate(model,glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model,glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model,glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        const float radius =  10.0f;
        view = camera->view();
        glm::mat4 mvp = proj * view * model;
        ps.setUniMat4f("aMVP", mvp);
        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
            camera->SetStatus(true);
        if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            camera->SetStatus(false);
    }

    void TestCube::onRender()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0,0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        renderer->draw(vao, ebo, ps);
    }

    void TestCube::onImGuiRender()
    {
        ImGui::SliderFloat("distance", &distance, -10.0f, 10.0f);
        ImGui::SliderFloat3("rotation", &rotation.x, -1.0f, 1.0f);
        //ImGui::SliderFloat("move1", &move1, -2.0f, 2.0f);
    }


    void TestCube::passWindow(GLFWwindow *_window){
        window = _window;
    }


    void TestCube::processInput(float deltatime)
    {
        const float cameraSpeed = 3.0f * deltatime;
    }

}
