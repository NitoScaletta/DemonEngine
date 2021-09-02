#include "TestDirLight.h"


namespace test{

    TestDirLight::TestDirLight(GLFWwindow* wind, Camera* cam) : window(wind),
                                                                size(100),
                                                                camera(cam),
                                                                TestDir(glm::vec3(1.0f))
    {
        light = new Flashlight(camera);
        constant = 1;
        linear = 0.09f;
        quadratic = 0.032f;
        texture1.Set("container2.png", GL_TEXTURE0);
        specular1.Set("vc.png", GL_TEXTURE1);
        texture2.Set("wall.jpg", GL_TEXTURE2);
        specular2.Set("walls.jpg", GL_TEXTURE3);
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
            cubes.back().ps.setUniMat4f("model", cubes.back().model());
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
        plane.ps.setUniMat4f("model", plane.model());

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
        light->ps.setUniVec3("aColor", light->lightColor);

        for(int i =0; i < size; i++)
        {
            cubes[i].UpdateMVP(proj, view);
            cubes[i].setUniFlashlight(light);
            cubes[i].setUniLight(light);
            cubes[i].setUniMaterial(light->lightColor);
            cubes[i].ps.setUniVec3("viewPos", camera->cameraPosition);
        }


        plane.UpdateMVP(proj, view);
        plane.setUniLight(light);
        plane.setUniMaterial(light->lightColor);
        plane.ps.setUniVec3("viewPos", camera->cameraPosition);

         camera->statusController();
    }


    void TestDirLight::onRender()
    {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        //cube->draw(renderer);
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
    }
}
