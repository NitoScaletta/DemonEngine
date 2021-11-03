
#include "TestModel.h"
#include "core/CoreFun.h"


namespace test{

void loadModel(Model* model)
{
    model->load("backpack/backpack.obj");
}

TestModel::TestModel(Camera* cam):
camera(cam) 
{
    Timer timer("model laoding");
    //Model models[10];
    //std::future<void> m_future[10];
    //for(int i = 0; i < 10; i++) 
    //{
    //    m_future[i] = std::async(std::launch::async, loadModel, &models[i]);
    //    std::cout << "loading model " << i << '\n';
    //}
    //for(int i = 0; i < 10; i++)
    //{
    //    m_future[i].wait();
    //}
    model = new Model("backpack/backpack.obj");
    proj = core::proj3d(4/3);
    view = camera->view();
    model_mat = glm::mat4(1.0f);
    glm::mat4 mvp = proj * view * model_mat;
    model->GetShaderProgram()->setUniMat4f("aMVP", mvp);
    model->GetShaderProgram()->setUnifi("texture1", 0);
}



void TestModel::onUpdate(float deltatime) 
{

    view = camera-> view();
    glm::mat4 mvp = proj * view * model_mat;
    model->GetShaderProgram()->setUniMat4f("aMVP", mvp);
    camera->statusController();
}

void TestModel::onRender() 
{
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        model->draw();
}

void TestModel::onImGuiRender() 
{

}

}