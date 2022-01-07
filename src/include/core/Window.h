#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <iostream>
#include <GLFW/glfw3.h>
#include <core/Events/Events.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class CrossPlatformWindow 
{
    public:

        using EventCallbackFn = std::function<void(Event&)>;
        ~CrossPlatformWindow(); 
        static void init(const char* name) { ApplicationName = name; s_window->_init(); }
        static bool ShouldClose ()       { return glfwWindowShouldClose(s_glfwwindow); } 
        static float AspectRatio()       { return s_window->_AspectRatio(); }
        static uint16_t GetWidth()       { return s_window->_GetWidth(); }
        static uint16_t GetHeight()      { return s_window->_GetHeight(); }
        static glm::vec2 GetResolution() { 
            return glm::vec2(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
        }
        static void SetVSync(bool vsync) { glfwSwapInterval(vsync); s_window->m_Data.VSync = vsync;}
        static void SetEventCallBack(const EventCallbackFn& callback)   
        { Get()->_SetEventCallback(callback); }
        static float CalcDeltaTime();
        static const float& GetDeltaTime()  { return m_deltaTime; };
        static void CaptureCursor()         { glfwSetInputMode(GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);}
        static void ReleaseCursor()         { glfwSetInputMode(GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
        static CrossPlatformWindow* Get()   { return s_window; }
        static GLFWwindow* GetNativeWindow()     { return s_glfwwindow; }
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
            m_Data.EventCallback.push_back(callback);
        }





        GLFWwindow *window;
        static GLFWwindow *s_glfwwindow;
        static CrossPlatformWindow* s_window;
        struct WindowData
        {
            uint16_t width;
            uint16_t height;
            bool VSync;
            std::vector<EventCallbackFn> EventCallback;
        };
        WindowData m_Data;
        float LastFrame = 0;
        static float m_deltaTime;
        static std::string ApplicationName;
};

using Window = CrossPlatformWindow;
#endif // __WINDOW_H__