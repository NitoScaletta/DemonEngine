#include <Renderer/ParticleSystem.h>
#include <core/profiling/Timer.h>
#include <core/Log.h>
#include "core/Random.h"




ParticleSystem::ParticleSystem() : ParticleIndex(0) 
{
    particles.resize(MaxParticles);
    nParticles = MaxParticles;
}


ParticleSystem::ParticleSystem(std::shared_ptr<Texture> texture) : m_Texture(texture), ParticleIndex(0)
{
    particles.resize(MaxParticles);
    nParticles = MaxParticles;
}



ParticleSystem::ParticleSystem(std::shared_ptr<SubTexture> tile) : m_Tile(tile), ParticleIndex(0)
{
    particles.resize(MaxParticles);
    nParticles = MaxParticles;
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
    particles[ParticleIndex].SpawnTime = Timer::GetTimeFloat();
    particles[ParticleIndex].Scale = props.Scale;
    particles[ParticleIndex].RotationPerTimeStep = props.RotationPerTimeStep;
    particles[ParticleIndex].Color = props.Color;
    particles[ParticleIndex].Shape = props.Shape;
    particles[ParticleIndex].FadingStep = props.FadingStep;
    particles[ParticleIndex].ScalingStep = props.ScalingStep;
    ParticleIndex++;
}



void ParticleSystem::onRender() 
{
    float deltatime = Window::GetDeltaTime();
    for(auto& particle : particles)
    {
        if(!particle.isActive)
            continue;

        if((Timer::GetTimeFloat() - particle.SpawnTime) >= particle.LifeTime)
        {
            particle.isActive = false;
            continue;
        }
        particle.Scale -= particle.ScalingStep * deltatime;
        if(particle.Scale <= 0)
        {
            particle.isActive = false;
            continue;
        }
        particle.Position =  particle.Position + particle.Velocity;
        particle.Rotation += particle.RotationPerTimeStep;
        particle.Color.w  -= particle.FadingStep * deltatime;


        switch (particle.Shape)
        {
        case ParticleShape::Circle:
        {
        	glm::mat4 model =  glm::translate(IdMatrix, particle.Position);
        	model = glm::scale(model,{particle.Scale, particle.Scale, 1});
            Renderer::DrawCircle(model, particle.Color);
        }
	    break;

	    case ParticleShape::Quad:
	    {
            glm::mat4 model =  glm::translate(IdMatrix, particle.Position);
		    model = glm::scale(model,{particle.Scale, particle.Scale, 1});
		    model = glm::rotate(model, glm::radians(particle.Rotation), { 0, 0, 1 });
            Renderer::DrawQuad(model, particle.Color);
        }
            break;
        case ParticleShape::Textured:
            Renderer::DrawTexturedQuad(particle.Position, m_Texture, particle.Scale, particle.Rotation, 1.0f, particle.Color);
            break;

        case ParticleShape::Tile:
            Renderer::DrawSprite(particle.Position, m_Tile, particle.Scale, particle.Rotation, particle.Color);
            break;
        }
        
    }
}



void ParticleProps::RandomValues() 
{
    Scale = Random::Float()/8;
    int vx, vy;
    Random::Float() > 0.5f ? vx = 1 : vx = -1;
    Random::Float() > 0.5f ? vy = -1 : vy = 1;
    Velocity = {    Random::Float() * vx * Window::GetDeltaTime(), 
                    Random::Float() * vy * Window::GetDeltaTime(),
                    0}; 
    int RotationSense;
    Random::Float() > 0.5 ? RotationSense = 1 : RotationSense = -1;
    RotationPerTimeStep *= RotationSense * 300.0f * Window::GetDeltaTime();

}


