#include "TestPointLight.h"


namespace test{

    TestPointLight::TestPointLight(GLFWwindow* wind, Camera* cam) : window(wind),
                                                                size(100),
                                                                camera(cam),
                                                                TestDir(glm::vec3(1.0f))
    {
        cube = new Cube("fragment.txt");
        proj = core::proj3d(4/3);
        view = camera->view();

        cube->SetPos(1, 1, 1);
        cube->UpdateMVP(proj, view);
        cube->ps.setUniMat4f("model",cube->model());
    }


    void TestPointLight::onUpdate(float deltatime)
    {
        view = camera->view();
        cube->UpdateMVP(proj, view);

         camera->statusController();
    }


    void TestPointLight::onRender()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        cube->draw(renderer);
        //light->draw(renderer);
    }


    void TestPointLight::onImGuiRender()
    {

    }
}
