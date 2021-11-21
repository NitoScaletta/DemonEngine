#include <Renderer/ParticleSystem.h>
#include <core/profiling/Timer.h>


ParticleQuad::ParticleQuad() 
{
    Shader vs, fs;
    Vertex vertices[4];
    vertices[0].setPos(-0.5f, -0.5f);
    vertices[0].setCol(0.5f, 0.5f, 0.0f, 1.0f);
    vertices[1].setPos( 0.5f, -0.5f);
    vertices[1].setCol(0.5f, 0.5f, 0.0f, 1.0f);
    vertices[2].setPos( 0.5f, 0.5f);
    vertices[2].setCol(0.5f, 0.5f, 0.0f, 1.0f);
    vertices[3].setPos(-0.5f, 0.5f);
    vertices[3].setCol(0.5f, 0.5f, 0.0f, 1.0f);
    int32_t indices[6] = { 0, 1, 2 , 2, 3, 0};
    ElementBuffer ebo;
    vao.bind();
    ebo.bind();
    vbo.bindDynamic(4);
    vao.newLayoutDynamic();
    ebo.set(indices, sizeof(int32_t)* 6);
    vbo.loadDynamic(0, sizeof(Vertex)* 4, vertices);
    vs.initShader(VERTEX_SHADER);
    fs.initShader(FRAGMENT_SHADER);
    vs.readSourceFile("VertexQuad.glsl");
    fs.readSourceFile("QuadFragment.glsl");
    ps.compileShader(vs.id,fs.id);
}



ParticleSystem::ParticleSystem() : ParticleIndex(0) 
{
    particles.resize(1000);
}


void ParticleSystem::Emit(ParticleProps& props)
{
    if(ParticleIndex == nParticles)
    {
        ParticleIndex = 0;
        core::msg("reset");
    }
    particles[ParticleIndex].Position = {props.x, props.y, 0};
    particles[ParticleIndex].LifeTime = props.LifeTime;
    particles[ParticleIndex].Velocity = props.Velocity;
    particles[ParticleIndex].isActive = true;
    particles[ParticleIndex].SpawnTime = Timer::GetTimeFloat();
    particles[ParticleIndex].Scale = props.Scale;
    particles[ParticleIndex].RotationPerTimeStep = props.RotationPerTimeStep;
    ParticleIndex++;
}



void ParticleSystem::onRender(glm::mat4 viewprojmatrix) 
{
    for(auto& particle : particles)
    {
        if(!particle.isActive)
            continue;

        if((Timer::GetTimeFloat() - particle.SpawnTime) >= particle.LifeTime)
        {
            particle.isActive = false;
            continue;
        }
        particle.Scale -= 0.1 * Window::GetDeltaTime();
        if(particle.Scale <= 0)
        {
            particle.isActive = false;
            continue;
        }
        particle.Position =  particle.Position + particle.Velocity;
        particle.Rotation = particle.Rotation + particle.RotationPerTimeStep * CrossPlatformWindow::GetDeltaTime();
        glm::mat4 model =  glm::translate(glm::mat4(1.0f), particle.Position);
        model = glm::scale(model,{particle.Scale, particle.Scale, 1});
        model = glm::rotate(model, glm::radians( particle.Rotation), {0.0f,0.0f,1.0f} );
        glm::mat4 mvp = viewprojmatrix * model;
        particleQuad.GetShaderProgram().setUniMat4f("aMVP", mvp);
        particleQuad.GetVertexArray().bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr );
    }
}

