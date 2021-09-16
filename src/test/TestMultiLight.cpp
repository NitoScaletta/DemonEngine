#include "TestMultiLight.h"
namespace test
{
    TestMultiLight::TestMultiLight(Camera* cam, GLFWwindow * window) :  camera(cam),
                                                                        n_pointlight(10) 
    {
        Timer timer("MultiLight");

        Texture texture[2];
        texture[0].Set("container2.png", GL_TEXTURE0);
        texture[1].Set("vc.png", GL_TEXTURE1);
        texture[0].active();
        texture[1].active();
        glEnable(GL_DEPTH_TEST);



        proj = core::proj3d(4/3);
        view = camera->view();


        int x = 0, y =0;
        for(int i = 0; i <  100; i++)
        {
            cubes.push_back(Cube("fragmentMulti.txt"));
            cubes.back().SetPos(x,y,y);
            cubes.back().SetDiffuseMap(0);
            cubes.back().SetSpecularMap(1);
            cubes.back().UpdateMVP(proj, view);
            cubes.back().setUniModel();
            if((i + 1 )%5 == 0 && i != 0)
            {
                y++;
                x = 0;
                }
            else x++;
        }
        dirlight = new DirectionalLight;
        dirlight->SetDir(glm::vec3(1.0f));
        dirlight->UpdateMVP(proj,view);

        for(int i = 0; i<n_pointlight; i++)
        {
            pointlight.push_back(PointLight());
            pointlight.back().SetPos((i*2) - 4, 0, -7);
            light_position[i] = pointlight.back().pos;
            pointlight.back().UpdateMVP(proj, view);
        }

        flashlight = new Flashlight(camera);
        flashlight->cutOff = 10.0f;
        flashlight->fade = 5.0f;


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
        for(int i = 0; i<cubes.size(); i++)
        {
            cubes[i].UpdateMVP(proj, view);
            cubes[i].setUniDirLight(dirlight);
            cubes[i].setUniPointLightArray(pointlight.data(), n_pointlight);
            cubes[i].setCameraPosition(camera);
            cubes[i].setUniMaterial(dirlight->lightColor);
            cubes[i].setUniFlashlight(flashlight);
        }


        for(int i = 0; i < pointlight.size(); i++)
        {
            pointlight[i].UpdateMVP(proj, view);
            pointlight[i].SetPos(light_position[i]);
            pointlight[i].setCubeColor();
        }
    
        plane->UpdateMVP(proj,view);
        camera->statusController();
    }
    
    void TestMultiLight::onRender() 
    {
        glClearColor(0.3f,0.5f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Renderer* renderer;
        for(int i = 0; i<cubes.size(); i++)
            cubes[i].draw(renderer);
        plane->draw(renderer);
        for(int i= 0; i <pointlight.size(); i++)
            pointlight[i].draw(renderer);
    }
    
    void TestMultiLight::onImGuiRender() 
    {
        if(ImGui::CollapsingHeader("DirectionalLight"))
        {
            ImGui::SliderFloat ("directional light ambient inf", &dirlight->ambientInf, 0.0f, 1.0f);
            ImGui::SliderFloat ("directional light diffuse inf", &dirlight->diffuseInf, 0.0f, 1.0f);
            ImGui::SliderFloat3("directional light direction",  &dirlight->direction.x, 0.0f, 1.0f);
        }

        for(int i = 0; i < n_pointlight; i++)
        {
            if (ImGui::CollapsingHeader(std::string("light n "+std::to_string(i)).c_str()))
            {
                ImGui::ColorEdit3(std::string  ("color "                 +std::to_string(i)).c_str(),  &pointlight[i].lightColor.x);
                ImGui::SliderFloat (std::string("point light ambient inf"+std::to_string(i)).c_str(),  &pointlight[i].ambientInf, 0.0f, 1.0f);
                ImGui::SliderFloat (std::string("point light diffuse inf"+std::to_string(i)).c_str(),  &pointlight[i].diffuseInf, 0.0f, 1.0f);
                ImGui::SliderFloat (std::string("point light linear"     +std::to_string(i)).c_str(),  &pointlight[i].linear, 0.0f, 0.1f);
                ImGui::SliderFloat (std::string("point light quadratic"  +std::to_string(i)).c_str(),  &pointlight[i].quadratic, 0.0f, 0.1f);
                ImGui::SliderFloat3(std::string("position"               +std::to_string(i)).c_str(),  &light_position[i].x, -8.0f, 8.0f);
            }
        }

        if(ImGui::CollapsingHeader("Flash light"))
        {
            ImGui::SliderFloat ("flashlight ambient inf" , &flashlight->ambientInf, 0.0f, 1.0f);
            ImGui::SliderFloat ("flashlight diffuse inf" , &flashlight->diffuseInf, 0.0f, 1.0f);
            ImGui::SliderFloat ("flashlight linear"      , &flashlight->linear, 0.0f, 0.1f);
            ImGui::SliderFloat ("flashlight quadratic"   , &flashlight->quadratic, 0.0f, 0.1f);
            ImGui::SliderFloat ("flashlight  circle"     , &flashlight->cutOff, 0.0f, 0.1f);
            ImGui::SliderFloat ("point light quadratic"  , &flashlight->fade, 0.1f, 10.0f);
        }

    }
}