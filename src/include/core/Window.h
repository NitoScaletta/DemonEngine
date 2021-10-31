#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
    public: 
        Window();
        ~Window();
        virtual void init() = 0;

    protected:
        int16_t x;
        int16_t y;

};



class WindowsWindow : public Window
{
    public:
        WindowsWindow();
        ~WindowsWindow();
        void init() override;

    private:
        GLFWwindow *window;

};


#endif // __WINDOW_H__