#include "TestMultiLight.h"
namespace test
{
    TestMultiLight::TestMultiLight(Camera* cam, GLFWwindow * window) : camera(cam) 
    {
        Timer timer("MultiLight");

        Texture texture[2];
        texture[0].Set("container2.png", GL_TEXTURE0);
        texture[1].Set("vc.png", GL_TEXTURE1);
        texture[0].active();
        texture[1].active();



        proj = core::proj3d(4/3);
        view = camera->view();

        cube = new Cube("fragmentMulti.txt");
        cube->SetPos(0,0,0);
        cube->SetScale(2);
        cube->SetDiffuseMap(0);
        cube->SetSpecularMap(1);
        //cube->setUniModel();
        cube->UpdateMVP(proj, view);
        // cube->getPS()->setUniVec3("aColor",glm::vec3(0.4f, 0.3f, 0.1f));

        light = new DirectionalLight;
        light->SetPos(0, 0, -3);
        light->UpdateMVP(proj, view);
        light->SetDir(glm::vec3(1.0f));
        light->ambientInf = 0.2f;


        plane = new Plane;
        plane->SetPos(0,-3, 1);
        plane->UpdateMVP(proj,view);
        plane->setUniModel();
        plane->SetDiffuseMap(0);
        plane->SetSpecularMap(1);
    }

    void TestMultiLight::onUpdate(float deltatime) 
    {
        view = camera->view();
        // cube->setCameraPosition(camera);
        cube->UpdateMVP(proj, view);
        cube->setUniDirLight(light);
    
        plane->UpdateMVP(proj,view);

        light->UpdateMVP(proj, view);
        camera->statusController();
    }
    
    void TestMultiLight::onRender() 
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        cube->draw(renderer);
        light->draw(renderer);
        plane->draw(renderer);
    }
    
    void TestMultiLight::onImGuiRender() 
    {
        ImGui::SliderFloat("ambient inf", &light->ambientInf, 0.0f, 1.0f);
        ImGui::SliderFloat("diffuse inf", &light->diffuseInf, 0.0f, 1.0f);
        ImGui::SliderFloat3("direction", &light->direction.x, 0.0f,1.0f);
    }
}