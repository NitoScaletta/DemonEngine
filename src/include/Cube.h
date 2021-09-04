#ifndef CUBE_H_
#define CUBE_H_

#include "core.h"

class PhongLight;
class DirectionalLight;
class PointLight;
class Flashlight;



class Shape
{
        public:
                ShaderProgram ps;
                glm::mat4 Model;
                bool shouldbeDraw;
                Material material;
                glm::vec3 pos;
                glm::vec3 scale;
                glm::mat4 model();


                Shape() : shouldbeDraw(true){};
                ~Shape(){};
                void draw(Renderer* rend);
                void SetTexture(unsigned int texture_id);
                void SetDiffuseMap(unsigned int texture_id);
                void SetSpecularMap(unsigned int texture_id);
                void SetPos(float x = 0.0f, float y = 0.0f, float z =0.0f);
                void UpdateMVP(glm::mat4 proj,glm::mat4 view);
                void setUniLight(PhongLight* light);
                void setUniDirLight(DirectionalLight* light);
                void setUniPointLight(PointLight* light);
                void setUniFlashlight(Flashlight* light);
                void setUniMaterial(glm::vec3 lightColor, glm::vec3 spec = glm::vec3(1.0f));

        protected:
                std::string name;
                std::vector<Vertex> vertices;
                VertexArray vao;
                VertexBuffer vbo;
                ElementBuffer ebo;
                Shader vs, fs;
                glm::vec3 rotation;
};




class Cube : public Shape
{
        public:
                Cube(){};
                Cube(const char* vertexshader);
                ~Cube();

                void unbind();
                void SetScale(float Scale);
        private:
                Vertex vertArr[24];
                void CreateBuffer();

};


class Plane : public Shape
{
        public:
                Plane();

        private:
                void CreateBuffer();

};

#endif // CUBE_H_
