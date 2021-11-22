#include "include/TestSpawnQuad.h"
#include "core/Input.h"
#include <core/Random.h>



namespace test{


TestSpawQuad::TestSpawQuad() 
{
    
    Random::init();
    CrossPlatformWindow::SetEventCallBack(BIND_EVENT(TestSpawQuad::onEvent));
    ParticleProps props;
    props.x = 0;
    props.y = 0;
    props.LifeTime = 10;
    props.Velocity = {1,1,0};
    particles.Emit(props);
    quad = new Quad(0,0, 1);
}

void TestSpawQuad::onUpdate(float deltatime) 
{
    camera.movement(deltatime);
    quad->onUpdate(camera.GetViewProjMatrix());
}

void TestSpawQuad::onRender() 
{
    quad->draw();
    particles.onRender(camera.GetViewProjMatrix());
}

void TestSpawQuad::onImGuiRender() 
{
}


void TestSpawQuad::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(TestSpawQuad::onMouseMovedEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(TestSpawQuad::onKeyPressedEvent));
}


bool TestSpawQuad::onMouseMovedEvent(MouseMovedEvent& e) 
{
    glm::vec4 color = {0.6f, 0.4, 0.2f, 1.0f};
    worldspacex = camera.GetMousePositionInWorldSpceX(e.GetMouseX());
    worldspacey = camera.GetMousePositionInWorldSpceY(e.GetMouseY());
    ParticleProps props;
    props.x = worldspacex;
    props.y = worldspacey;
    props.Color = color;
    for(int i = 0; i < 10; i++)
    {
        props.RandomValues();
        particles.Emit(props);
    }
    return true;
}


bool TestSpawQuad::onKeyPressedEvent(KeyPressedEvent& e) 
{
    return true;
}




}