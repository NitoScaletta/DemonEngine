#ifndef __QUAD_H__
#define __QUAD_H__

#include <Renderer/glObjects.h>
#include <Renderer/Shader.h>
#include<core/core.h>
#include<core/profiling/Timer.h>
#include <Renderer/renderer.h>
#include <core/Random.h>




class Quad
{
    public:
    Quad(float pos_x = 0, float pos_y = 0, float size = 1);
    ~Quad(){};
    void onUpdate(glm::mat4 viewproojmatrix);
    void SetVelocity(glm::vec3 _velocity)   { velocity = _velocity; velocity.z = 0;};
    void SetVelocity(float x, float y)      { velocity.x = x; velocity.y = y; }
    void draw();
    ShaderProgram& GetProgranShader() { return ps; }

    private:
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
    Shader vs, fs;
    ShaderProgram ps;
    Vertex vertices[4];
    int32_t indices[6] = { 0, 1, 2, 2, 3, 0};;
    float rotation = 0;
    glm::vec3 velocity; 
    glm::vec3 position = { 0, 0, 0};
    void CreateVertices(float pos_x = 0, float pos_y = 0, float size = 1);

};
#endif // __QUAD_H__