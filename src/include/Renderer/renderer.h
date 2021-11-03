#ifndef RENDERER_H_
#define RENDERER_H_
#include <core/core.h>
#include <Renderer/Camera2d.h>

class Renderer
{
    public:
        Renderer(float x, float y);
        ~Renderer();
        Camera2d* camera;
        GLFWwindow* WindowInit();
        void draw(VertexArray& vao, ElementBuffer& ebo, ShaderProgram& ps);

        void init();
        void Clear(float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
        void End();
        void update();

        void ImGuiInit();
        void ImGuiStart();
        void ImGuiEnd();    
        void ImGuiClose();    

        void updateResolution(const float x, const float y);
        inline GLFWwindow* GetWindowPointer() const { return wind; }
        inline void SetWindow(GLFWwindow *window) { wind = window;}
        

    private:
        float wind_size_x, wind_size_y;
        GLFWwindow* wind;

};

#endif // RENDERER_H_
