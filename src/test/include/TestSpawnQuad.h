#ifndef __TESTSPAWNQUAD_H__
#define __TESTSPAWNQUAD_H__
#include <test.h>
#include <meshes/quad.h>
#include <Renderer/Camera2dController.h>
#include <core/Events/MouseEvents.h>
#include  <core/Events/KeyEvents.h>
#include <core/profiling/Timer.h>
#include <Renderer/ParticleSystem.h>

namespace test
{
    class TestSpawQuad : public Test
    {
        public:
        TestSpawQuad();
        virtual void onUpdate(float deltatime) override;
        virtual void onRender() override;
        virtual void onImGuiRender() override;
        virtual void onEvent(Event& e) override;
        bool onMouseMovedEvent(MouseMovedEvent& e);
        bool onKeyPressedEvent(KeyPressedEvent& e);

        private:
        Quad* quad;
        Camera2dController camera;
        float worldspacex = 0, worldspacey = 0;
        float timestep;
        ParticleSystem particles;

    };
    
    
}

#endif // __TESTSPAWNQUAD_H__