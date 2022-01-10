#ifndef __TESTSPAWNQUAD_H__
#include <test.h>
#include <core/Log.h>
#include <Renderer/Camera2dController.h>
#include <core/Events/MouseEvents.h>
#include <core/Events/KeyEvents.h>
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
        bool onMouseScrolledEvent(MouseScrolledEvent& e);

        private:
        Camera2dController camera;
        float worldspacex = 0, worldspacey = 0;
        ParticleSystem particles;

    };
    
    
}

#endif // __TESTSPAWNQUAD_H__