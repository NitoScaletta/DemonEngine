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
}

void TestSpawQuad::onImGuiRender() 
{
    quad->draw();
    particles.onRender(camera.GetViewProjMatrix());
}


void TestSpawQuad::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(TestSpawQuad::onMouseMovedEvent));
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(TestSpawQuad::onKeyPressedEvent));
}


bool TestSpawQuad::onMouseMovedEvent(MouseMovedEvent& e) 
{
    float speed = 1 * Window::GetDeltaTime();
    float x,y, vx, vy;
    x = camera.GetMousePositionInWorldSpceX(e.GetMouseX());
    y = camera.GetMousePositionInWorldSpceY(e.GetMouseY());
    x > worldspacex ? vx = 1 : vx = -1;
    y > worldspacey ? vy = -1 : vy = 1;
    ParticleProps props;
    props.x = worldspacex;
    props.y = worldspacey;
    props.Scale = 1.0f/10.0f;
    props.Velocity = {vx*Random::Float()* speed, vy*Random::Float()* speed, 0};
    props.LifeTime = 10.0f;
    int RotationSense;
    Random::Float() > 0.5 ? RotationSense = 1 : RotationSense = -1;
    props.RotationPerTimeStep = RotationSense * 300.0f;
    particles.Emit(props);
    worldspacex = x;
    worldspacey = y;
    return true;
}


bool TestSpawQuad::onKeyPressedEvent(KeyPressedEvent& e) 
{
    return true;
}




}