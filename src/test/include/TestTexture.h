#ifndef __TESTTEXTURE_H__
#define __TESTTEXTURE_H__

#include <test.h>
#include <Renderer/renderer.h>
#include <core/Events/Events.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/MouseEvents.h>
#include <core/Events/ApplicationEvents.h>
#include <core/core.h>
#include <Renderer/Camera2dController.h>
#include <meshes/quad.h>

namespace test
{
    class TestTexture : public Test
    {
        public:
            TestTexture();
            ~TestTexture(){};
            virtual void onUpdate(float deltatime) override;
            virtual void onRender() override;
            virtual void onImGuiRender() override;
            virtual void onEvent(Event& e) override;
            bool onKeyPressed(KeyPressedEvent& e);
            bool onWindowResizedEvent(WindowResizeEvent& e);
            bool onMouseScrolledEvent(MouseScrolledEvent& e);
            bool onMouseMovementEvent(MouseMovedEvent& e);

        private:
            int animFrame = 0;
            VertexArray vao;
            VertexBuffer vbo;
            ElementBuffer ebo;
            Shader vs,fs;
            ShaderProgram ps;
            Vertex* vertices;
            Texture texture;
            void createVertices();
            std::vector<int> indices;
            Camera2dController camera;
    };
  
}
#endif // __TESTTEXTURE_H__