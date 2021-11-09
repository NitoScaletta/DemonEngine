#ifndef RENDERER_H_
#define RENDERER_H_
#include <core/core.h>
#include <Renderer/Camera2d.h>

class Renderer
{
    public:
        ~Renderer();
        static void draw(VertexArray& vao, ElementBuffer& ebo, ShaderProgram& ps);

        static void init();
        static void Clear(float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
        static void End();

        static void ImGuiInit();
        static void ImGuiStart();
        static void ImGuiEnd();    
        static void ImGuiClose();    

        

    private:
        Renderer();
};

#endif // RENDERER_H_
