#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <core/core.h>
#include <meshes/quad.h>

struct ParticleProps
{
    float x, y, Scale;
    float LifeTime,RotationPerTimeStep;
    glm::vec3 Position;
    glm::vec3 Velocity;

};


class ParticleQuad
{
    public:
    ParticleQuad();
    ~ParticleQuad(){}
    VertexArray GetVertexArray()        {   return vao; }
    ShaderProgram GetShaderProgram()    {   return ps;  }
     
    private:
    VertexArray vao;
    VertexBuffer vbo;
    ShaderProgram ps;
};

class ParticleSystem
{
    public:
    ParticleSystem();
    void Emit(ParticleProps& prop);
    void onRender(glm::mat4 viewprojmatrix);

    private:
    uint16_t ParticleIndex;
    uint16_t nParticles = 999;
    struct Particle{
        float LifeTime, SpawnTime;
        bool isActive;
        float Scale, RotationPerTimeStep, Rotation = 0;
        glm::vec3 Position;
        glm::vec3 Velocity;

    };
    ParticleQuad particleQuad;
    std::vector<Particle> particles;
};

   







//bool ShouldBeDestroyed() { if((Timer::GetTimeFloat() - TimeStart) >= LifeTime) return true; else return false; }
#endif // __PARTICLESYSTEM_H__