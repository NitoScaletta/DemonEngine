#include <core/Window.h>
#include <assert.h>
#include <core/Events/MouseEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/ApplicationEvents.h>


CrossPlatformWindow::CrossPlatformWindow(Renderer& rend) : renderer(rend)
{
    m_Data.width = 1280;
    m_Data.height = 720; 
}

CrossPlatformWindow::~CrossPlatformWindow() 
{

}

void CrossPlatformWindow::init() 
{
    if (!glfwInit())
    {
        std::cout << "errore nella creazione della finestra" << '\n';
        assert(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(m_Data.width, m_Data.height, "DemonEngine", NULL, NULL);
    if (!window)
    {
        std::cout << "Impossibile creare finestra glfw" << '\n';
        glfwTerminate();
        window = nullptr;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SetVSync(0);
    glfwSetWindowUserPointer(window, &m_Data);
    LastFrame = glfwGetTime();

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int x, int y){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.width = x;
        data.height = y;
        WindowResizeEvent event(x,y);
        data.EventCallback(event);
        glViewport(0,0, x, y);
        }
    );
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event(xpos, ypos);
        data.EventCallback(event);
        
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window,double xoffset, double yoffset){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event(xoffset, yoffset);
        data.EventCallback(event);

    });
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,1);  
                    data.EventCallback(event);
                    break;
                }
            }

            if(glfwGetKey(window , GLFW_KEY_P) == GLFW_PRESS)
                glfwSetInputMode(window , GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            if(glfwGetKey(window , GLFW_KEY_O) == GLFW_PRESS)
                glfwSetInputMode(window , GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        });
}





float CrossPlatformWindow::GetDeltaTime() 
{
    float DeltaTime;
    float CurrentFrame = glfwGetTime();
    DeltaTime = CurrentFrame - LastFrame;
    LastFrame = CurrentFrame;
    return DeltaTime;
}
        