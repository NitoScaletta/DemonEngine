#ifndef __INPUT_H__
#define __INPUT_H__

#include  <GLFW/glfw3.h>
#include <core/Events/KeyCodes.h>
#include <core/Window.h>



class Input{

    public:

        static bool isPressed(KeyCode  key) {
                if(glfwGetKey(CrossPlatformWindow::GetNativeWindow(), key) == GLFW_PRESS)
                    return true;
                
                return false;
        };

        static glm::vec2 GetMousePosition()
        {
            double xpos, ypos;
            glfwGetCursorPos(Window::GetNativeWindow(), &xpos, &ypos);
            return { xpos, ypos };
        }
        
    


    private:
        Input();
};

#endif // __INPUT_H__