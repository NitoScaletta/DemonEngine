#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <core/core.h>

enum class ParticleShape
{
    Quad, Circle 
};

struct ParticleProps
{
    float Scale;
    float LifeTime,RotationPerTimeStep;
    glm::vec3 Position;
    glm::vec3 Velocity;
    glm::vec4 Color;
    ParticleShape Shape;
    void RandomValues();
};





class ParticleSystem
{
    public:
    ParticleSystem();
    void Emit(ParticleProps& prop);
    void onRender();

    private:
    uint16_t ParticleIndex;
    uint16_t nParticles = 999;
    struct Particle{
        float LifeTime, SpawnTime;
        bool isActive;
        float Scale, RotationPerTimeStep, Rotation = 0;
        glm::vec3 Position;
        glm::vec3 Velocity;
        glm::vec4 Color;
        ParticleShape Shape;
    };
    std::vector<Particle> particles;
    const glm::mat4 m_IdMatrix = glm::mat4(1.0f);
};

   







//bool ShouldBeDestroyed() { if((Timer::GetTimeFloat() - TimeStart) >= LifeTime) return true; else return false; }
#endif // __PARTICLESYSTEM_H__