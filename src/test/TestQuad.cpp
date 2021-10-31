#include "glad/glad.h"
#include "TestQuad.h"
#include "imgui/imgui.h"
#include "Renderer/renderer.h"
#include "graphic/glObjects.h"
#include "graphic/Shader.h"
#include <iostream>
#include <vector>
#include "core/CoreFun.h"


namespace test{



    TestQuad::TestQuad() : quad_rotation(0.0f){
        //float vertices[] = {
        //-50.0f, -50.0f, 1.0f, 0.5f, 0.5f, 0.8f, 1.0f, 0.0f, 0.0f, 1.0f,
        // 50.0f, -50.0f, 1.0f, 0.5f, 0.5f, 0.8f, 1.0f, 1.0f, 0.0f, 1.0f,
        // 50.0f,  50.0f, 1.0f, 0.5f, 0.5f, 0.8f, 1.0f, 1.0f, 1.0f, 1.0f,
        //-50.0f,  50.0f, 1.0f, 0.5f, 0.5f, 0.8f, 1.0f, 0.0f, 1.0f, 1.0f
        //};
        int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        std::vector<Vertex> vertices;
        core::createBuffer(1, vertices, -50, -50);
        vao.bind();
        ebo.bind();
        ebo.set(indices,sizeof(indices));
        //vbo.bind(vertices, sizeof(vertices));
        vbo.bindDynamic(10);
        vbo.bindLayout(vao);
        vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
        vs.initShader(VertexType::VERTEX);
        fs.initShader(VertexType::FRAGMENT);
        vs.readSourceFile("vertex.txt");
        fs.readSourceFile("fragmentQuad.txt");
        ps.compileShader(vs.id, fs.id);
        ps.use();
        texture.Set("container.jpg", GL_TEXTURE0);
        ps.setUnifi("texture1",0);
        quad_scale = glm::vec3(1.0f);
        proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f , -1.0f, 200.0f);
        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0,0,0));
        model = glm::translate(glm::mat4(1.0f),glm::vec3(100.0f,100.0f,0));
        move = glm::vec3(0.0f, 0.0f, 0.0f);
        movecamera = glm::vec3(0.0f, 0.0f, 0.0f);
        glUseProgram(-1);
        vs.deleteShader();
        fs.deleteShader();
        vao.unbind();
        ebo.unbind();
        vbo.unbind();
    }

    TestQuad::~TestQuad(){
    }

    void  TestQuad::onUpdate(float deltatime) {
        ps.use();
        this->processInput();
        model = glm::translate(glm::mat4(1.0f),move);
        model = glm::scale(model, quad_scale);
        model = glm::rotate(model, glm::radians(quad_rotation), glm::vec3(0.0f,0.0f,1.0f));
        view = glm::translate(glm::mat4(1.0f), movecamera);
        mvp =  proj * view * model;
        ps.setUniMat4f("aMVP", mvp);
    }

    void  TestQuad::onRender(){
        Renderer renderer;
        glClearColor(0,0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.draw(vao, ebo, ps);
    }

    void  TestQuad::onImGuiRender(){
            ImGui::Begin("Quad");
            ImGui::Text("position.");    
            ImGui::SliderFloat3("face", &move.x, -500.0f, 500.0f);
            ImGui::SliderFloat3("camera", &movecamera.x, -500.0f, 500.0f);
            ImGui::SliderFloat3("Scale", &quad_scale.x, 0.0f, 5.0f);
            ImGui::SliderFloat("Rotation", &quad_rotation, 0.0f, 360.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                            1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
    }


    void TestQuad::passWindow(GLFWwindow* windowptr){
        window = windowptr;
    }


    void TestQuad::processInput()
    {
       if(glfwGetKey(window, GLFW_KEY_W) ==  GLFW_PRESS)
           move.y += 5.1f;
       if(glfwGetKey(window, GLFW_KEY_S) ==  GLFW_PRESS)
           move.y -= 5;
       if(glfwGetKey(window, GLFW_KEY_A) ==  GLFW_PRESS)
           move.x -= 5;
       if(glfwGetKey(window, GLFW_KEY_D) ==  GLFW_PRESS)
           move.x += 5;
       if(glfwGetKey(window, GLFW_KEY_R) ==  GLFW_PRESS)
           quad_rotation+=1.0f;
       if(glfwGetKey(window, GLFW_KEY_P) ==  GLFW_PRESS)
       {
           quad_scale.x+=0.1f;
           quad_scale.y+=0.1f;
       }
       if(glfwGetKey(window, GLFW_KEY_O) ==  GLFW_PRESS)
       {
           quad_scale.x-=0.1f;
           quad_scale.y-=0.1f;
       }


    }
}
