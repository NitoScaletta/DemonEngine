#include <Renderer/ParticleSystem.h>
#include <future>
#include <core/profiling/Timer.h>
#include <core/Log.h>
#include "core/Random.h"




ParticleSystem::ParticleSystem() : ParticleIndex(0) 
{
    particles.resize(15000);
    nParticles = 15000;
}


void ParticleSystem::Emit(ParticleProps& props)
{
    if(ParticleIndex == nParticles)
    {
        ParticleIndex = 0;
    }
    particles[ParticleIndex].Position = props.Position;
    particles[ParticleIndex].LifeTime = props.LifeTime;
    particles[ParticleIndex].Velocity = props.Velocity;
    particles[ParticleIndex].isActive = true;
    //particles[ParticleIndex].SpawnTime = Timer::GetTimeFloat();
    particles[ParticleIndex].Scale = props.Scale;
    particles[ParticleIndex].RotationPerTimeStep = props.RotationPerTimeStep;
    particles[ParticleIndex].Color = props.Color;
    particles[ParticleIndex].Shape = props.Shape;
    ParticleIndex++;
}



void ParticleSystem::onRender() 
{
    for(auto& particle : particles)
    {
        if(!particle.isActive)
            continue;

        //if((Timer::GetTimeFloat() - particle.SpawnTime) >= particle.LifeTime)
        //{
        //    particle.isActive = false;
        //    continue;
        //}
        particle.Scale -= 0.1 * Window::GetDeltaTime();
        if(particle.Scale <= 0)
        {
            particle.isActive = false;
            continue;
        }
        particle.Color.x -= 0.01f;
        particle.Position =  particle.Position + particle.Velocity;
        particle.Rotation = particle.Rotation + particle.RotationPerTimeStep;
        glm::mat4 model =  glm::translate(m_IdMatrix, particle.Position);
        model = glm::scale(model,{particle.Scale, particle.Scale, 1});
        if(particle.Shape == ParticleShape::Circle)
			Renderer::DrawCircle(model, particle.Color);
        else if (particle.Shape == ParticleShape::Quad)
        {
			model = glm::rotate(model, glm::radians( particle.Rotation), {0.0f,0.0f,1.0f} );
			Renderer::DrawQuad(model, particle.Color);

        }
        
    }
}



void ParticleProps::RandomValues() 
{
    Scale = Random::Float() / 9.0f;
    int vx, vy;
    Random::Float() > 0.5f ? vx = 1 : vx = -1;
    Random::Float() > 0.5f ? vy = -1 : vy = 1;
    Velocity = {    Random::Float() * vx * Window::GetDeltaTime(), 
                    Random::Float() * vy * Window::GetDeltaTime(),
                    0}; 
    LifeTime = Random::Float() * 5;
    int RotationSense;
    Random::Float() > 0.5 ? RotationSense = 1 : RotationSense = -1;
    RotationPerTimeStep = RotationSense * 300.0f * Window::GetDeltaTime();

}


