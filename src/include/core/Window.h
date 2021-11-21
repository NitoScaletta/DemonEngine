#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <GLFW/glfw3.h>
#include <core/Events/Events.h>


class CrossPlatformWindow 
{
    public:

        using EventCallbackFn = std::function<void(Event&)>;
        ~CrossPlatformWindow();
        static void init() { s_window->_init(); }
        static bool ShouldClose ()       { return glfwWindowShouldClose(s_glfwwindow); } 
        static float AspectRatio()       { return s_window->_AspectRatio(); }
        static uint16_t GetWidth()       { return s_window->_GetWidth(); }
        static uint16_t GetHeight()      { return s_window->_GetHeight(); }
        static void SetVSync(bool vsync) { glfwSwapInterval(vsync); s_window->m_Data.VSync = vsync;}
        static void SetEventCallBack(const EventCallbackFn& callback)   
                                            { Get()->_SetEventCallback(callback); }
        static float CalcDeltaTime();
        static float GetDeltaTime() { return m_deltaTime; };
        static void CaptureCursor()         { glfwSetInputMode(window_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
        static void ReleaseCursor()         { glfwSetInputMode(window_ptr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
        static CrossPlatformWindow* Get()   { return s_window; }
        static GLFWwindow* window_ptr()     { return s_glfwwindow; }
        static float GetTime()              { return glfwGetTime(); }
        static int GetTimeInt()             { return glfwGetTime(); }

    private:
        CrossPlatformWindow();
        void _init() ;
        inline bool _ShouldClose ()       { return glfwWindowShouldClose(window); } 
        inline float _AspectRatio()       { return static_cast<float>(m_Data.width)/static_cast<float>(m_Data.height); }
        inline uint16_t _GetWidth()       { return m_Data.width; }
        inline uint16_t _GetHeight()      { return m_Data.height; }
        void _SetEventCallback(const EventCallbackFn& callback)  {
            m_Data.EventCallback = callback;
        }





        GLFWwindow *window;
        static GLFWwindow *s_glfwwindow;
        static CrossPlatformWindow* s_window;
        struct WindowData
        {
            uint16_t width;
            uint16_t height;
            bool VSync;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
        float LastFrame = 0;
        static float m_deltaTime;
};

using Window = CrossPlatformWindow;
#endif // __WINDOW_H__