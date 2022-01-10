#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__
#include <core/core.h>
#include <core/Math.h>
#include "Renderer/Colors.h"

enum class ParticleShape
{
    Quad, Circle, Textured, Tile 
};

struct ParticleProps
{
    float Scale;
    float LifeTime = 3, RotationPerTimeStep = 0, FadingStep = 0, ScalingStep = 0;
    glm::vec3 Position = glm::vec3(0);
    glm::vec3 Velocity = glm::vec3(0);
    glm::vec4 Color = Color::White;
    ParticleShape Shape;
    void RandomValues();
};





class ParticleSystem
{
    public:
        ParticleSystem();
        ParticleSystem(std::shared_ptr<Texture> texture);
        ParticleSystem(std::shared_ptr<SubTexture> tile);
        ~ParticleSystem() {}
        void Emit(ParticleProps& prop);
        void onRender();

    private:
        const uint32_t MaxParticles = 15000;
        uint16_t ParticleIndex;
        uint16_t nParticles;
        struct Particle{
            float LifeTime, SpawnTime;
            bool isActive;
            float Scale, Rotation = 0, RotationPerTimeStep = 0, FadingStep, ScalingStep;
            glm::vec3 Position;
            glm::vec3 Velocity;
            glm::vec4 Color;
            ParticleShape Shape;
        };
        std::vector<Particle> particles;
        std::shared_ptr<Texture> m_Texture;
        std::shared_ptr<SubTexture> m_Tile;

};

   







//bool ShouldBeDestroyed() { if((Timer::GetTimeFloat() - TimeStart) >= LifeTime) return true; else return false; }
#endif // __PARTICLESYSTEM_H__