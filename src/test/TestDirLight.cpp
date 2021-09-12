#include "TestDirLight.h"
#include <thread>
#include "stb_image.h"

namespace test{

    void updateCube(Cube* cube, Flashlight* light, Camera* camera,
                    glm::mat4 *proj, glm::mat4 *view)
    {
        Timer timer("cube  update");
        cube->UpdateMVP(*proj, *view);
        cube->setUniFlashlight(light);
        cube->setUniLight(light);
        cube->setUniMaterial(light->lightColor);
        cube->setCameraPosition(camera);
    }

    TestDirLight::TestDirLight(GLFWwindow* wind, Camera* cam) : window(wind),
                                                                size(100),
                                                                camera(cam),
                                                                TestDir(glm::vec3(1.0f))
    {
        Timer timer("total ");
        light = new Flashlight(camera);
        constant = 1;
        linear = 0.09f;
        quadratic = 0.032f;
        std::string te[] = {"container2.png", "vc.png", "wall.jpg", "walls.jpg"};
        {
            for(int i = 0; i <4; i++)
                t_futures.push_back(std::async(std::launch::async, texture::loadText,
                                                &data[i], te[i]));
            for(int i = 0; i <4; i++)
                t_futures[i].wait();
        }

        texture1. DataSet("container2.png", GL_TEXTURE0, &data[0]);
        specular1.DataSet("vc.png", GL_TEXTURE1,    &data[1]);
        texture2. DataSet("wall.jpg", GL_TEXTURE2,  &data[2]);
        specular2.DataSet("walls.jpg", GL_TEXTURE3, &data[3]);
        texture1.active();
        specular1.active();
        texture2.active();
        specular2.active();

        proj = core::proj3d(4/3);
        view = camera->view();

        int x=0 , y=0;
        for(int i = 0; i < size; i++)
        {
            cubes.push_back(Cube("fragmentSpot.txt"));
            cubes.back().SetPos(x,y,y);
            cubes.back().UpdateMVP(proj, view);
            cubes.back().SetDiffuseMap(0);
            cubes.back().SetSpecularMap(1);
            cubes.back().setUniModel();

            if((i + 1 )%5 == 0 && i != 0)
            {
                y++;
                x = 0;}
            else x++;
        }

        plane.SetPos(0, -1.0f, 0);
        plane.UpdateMVP(proj, view);
        plane.SetDiffuseMap(2);
        plane.SetSpecularMap(3);
        plane.setUniModel();

        light->SetPos(1,1, 4);
        light->UpdateMVP(proj, view);
        light->cutOff = 10.0f;
        light->fade = 5.0f;

    }


    void TestDirLight::onUpdate(float deltatime)
    {
        view = camera-> view();
        light->UpdateMVP(proj, view);
        light->setOptions( constant, linear, quadratic);
        std::future<void> vecFuture[4];

        for(int i =0; i < size; i++)
        {
            cubes[i].UpdateMVP(proj, view);
            cubes[i].setUniFlashlight(light);
            cubes[i].setUniLight(light);
            cubes[i].setUniMaterial(light->lightColor);
            cubes[i].setCameraPosition(camera);
        }


        plane.UpdateMVP(proj, view);
        plane.setUniLight(light);
        plane.setUniMaterial(light->lightColor);
        plane.setCameraPosition(camera);

         camera->statusController();
    }


    void TestDirLight::onRender()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        plane.draw(renderer);
        light->draw(renderer);
        for(int i =0; i < size; i++)
        {
            cubes[i].draw(renderer);
        }
    }


    void TestDirLight::onImGuiRender()
    {
        ImGui::Checkbox("draw light sqare", &light->shouldbeDraw);
        ImGui::SliderFloat("Ambient inf", &light->ambientInf, 0, 1);
        ImGui::SliderFloat("diffuse inf", &light->diffuseInf, 0.0f, 1.0f);
        ImGui::SliderFloat3("light pos", &light->pos.x, -20.0f, 20.0f);
        ImGui::SliderFloat("cutoff", &light->cutOff, 0, 50);
        ImGui::SliderFloat("cutoffoffset", &light->fade, 0, 10);
        ImGui::SliderFloat("linaer", &linear, 0, 0.5f);
        ImGui::SliderFloat("quadratic", &quadratic, 0, 0.5f);
        ImGui::ColorEdit3("color", &light->lightColor.x);
    }
}
