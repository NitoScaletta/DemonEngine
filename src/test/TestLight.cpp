#include "TestLight.h"
#include "core/CoreFun.h"
#include "meshes/Light.h"
#include "glm/gtx/normal.hpp"

namespace test{

    TestLight::TestLight(GLFWwindow* wind, Camera* cam) :
        camera(cam),
        window(wind),
        s(40)
    {
        texture1.Set("container2.png", GL_TEXTURE0);
        texture2.Set("wall.jpg", GL_TEXTURE1);
        specular1.Set("vc.png", GL_TEXTURE2);
        specular2.Set("walls.jpg", GL_TEXTURE3);
        texture1.active();
        texture2.active();
        specular1.active();
        specular2.active();

        plane = new Plane();
        cube = new Cube[s]{"fragmentDiffuse.txt"};
        model = new glm::mat4[s+1];
        proj = core::proj3d(4/3);
        view = camera->view();
        int x = 0,y = 0;

        for(int i = 0; i < s; i++)
        {
            cube[i].SetPos(x, y, 0);
            model[i] = cube[i].model();
            cube[i].ps.setUniMat4f("model", cube[i].model());
            glm::mat4 mvp = proj * view * model[i];
            cube[i].ps.setUniMat4f("aMVP", mvp);
            //cube[i].SetTexture(0);
            cube[i].SetDiffuseMap(0);
            cube[i].SetSpecularMap(2);
            if((i + 1 )%5 == 0 && i != 0)
            {
                y++;
                x = 0;}
            else x++;

        }
        light = new PhongLight;
        light->SetPos(1, 0, 2);
        light->UpdateMVP(proj, view);

        plane->SetPos(0.0f, -1.0f, 0.0f);
        plane->SetDiffuseMap(1);
        plane->SetSpecularMap(3);
        model[s] = plane -> model();
        plane ->ps.setUniMat4f("model", plane -> model());
        glm::mat4 mvp = proj * view * model[s];
        plane->ps.setUniMat4f("aMVP", mvp);
    }

    void TestLight::onUpdate(float deltatime){
        view = camera->view();
        light -> UpdateMVP(proj, view);
        light->ps.setUniVec3("aColor", light->lightColor);
        for(int i = 0; i < s; i++)
        {
            cube[i].UpdateMVP(proj, view);
            cube[i].setUniLight(light);
            cube[i].setUniMaterial(light->lightColor);
            cube[i].ps.setUniVec3("viewPos",camera->cameraPosition);
        }


        plane ->UpdateMVP(proj, view);
        plane->setUniLight(light);
        plane->setUniMaterial(light->lightColor);
        plane->ps.setUniVec3("viewPos",camera->cameraPosition);

        camera->statusController();
    }

    void  TestLight::onRender(){
        glEnable(GL_DEPTH_TEST);
        glClearColor(0,0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;

        for(int i = 0; i < s; i++)
        {
            cube[i].draw(renderer);
        }
        if(light->shouldbeDraw)
            light->draw(renderer);
        plane->draw(renderer);
    }

    void  TestLight::onImGuiRender()
    {
        ImGui::Checkbox("draw light ", &light->shouldbeDraw);
        ImGui::SliderFloat("Ambient inf", &light->ambientInf, 0, 1);
        ImGui::SliderFloat("diffuse inf", &light->diffuseInf, 0.0f, 1.0f);
        ImGui::SliderFloat("Plane Shininess", &plane->material.shininess, 1.0f, 1024.0f);
        ImGui::SliderFloat3("light pos", &light->pos.x, -8.0f, 8.0f);
        ImGui::ColorEdit3("color", &light->lightColor.x);
    }
}
