#include "TestMultiLight.h"
namespace test
{
    TestMultiLight::TestMultiLight(Camera* cam, GLFWwindow * window) : camera(cam) 
    {
        Timer timer("MultiLight");
        proj = core::proj3d(4/3);
        view = camera->view();
        cube = new Cube("fragmentLight.txt");
        cube->SetPos(0,0,0);
        cube->SetScale(2);
        //cube->setUniModel();
        cube->UpdateMVP(proj, view);
        
    }

    void TestMultiLight::onUpdate(float deltatime) 
    {
        view = camera->view();
        // cube->setCameraPosition(camera);
        cube->UpdateMVP(proj, view);
        camera->statusController();
    }
    
    void TestMultiLight::onRender() 
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        cube->draw(renderer);
        
    }
    
    void TestMultiLight::onImGuiRender() 
    {
        
    }
}