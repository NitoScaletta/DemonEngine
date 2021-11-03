#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <Renderer/renderer.h>
#include <GLFW/glfw3.h>
#include <core/Events/Events.h>

class Window
{
    public: 
        using EventCallbackFn = std::function<void(Event&)>;
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void init() = 0;
        virtual bool ShouldClose() = 0;
        virtual float AspectRatio() = 0;
        virtual uint16_t GetWidth() = 0;
        virtual uint16_t GetHeight() = 0;
        virtual void SetVSync(bool vsync) = 0; 

    protected:

};



class CrossPlatformWindow : public Window
{
    public:

        CrossPlatformWindow(Renderer& rend);
        ~CrossPlatformWindow();
        void init() override;
        inline bool ShouldClose () override     { return glfwWindowShouldClose(window); } 
        inline GLFWwindow* ptrWindow()          { return window; }
        inline float AspectRatio() override        { return m_Data.width/m_Data.height; }
        inline uint16_t GetWidth()  override     { return m_Data.width; }
        inline uint16_t GetHeight() override     { return m_Data.height; }
        virtual void SetVSync(bool vsync) override   { glfwSwapInterval(vsync); m_Data.VSync = vsync;}
        float GetDeltaTime();
        inline void SetRenderer(Renderer& rend) {renderer = rend;}
        virtual void SetEventCallback(const EventCallbackFn& callback) override {
            m_Data.EventCallback = callback;
        }
        inline virtual void CaptureCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
        inline virtual void ReleaseCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}


    private:
        GLFWwindow *window;
        Renderer& renderer;
        struct WindowData
        {
            uint16_t width;
            uint16_t height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
        float LastFrame;
};


#endif // __WINDOW_H__