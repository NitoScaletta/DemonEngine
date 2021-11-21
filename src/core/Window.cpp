#include <core/Window.h>
#include <assert.h>
#include <core/Events/MouseEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/ApplicationEvents.h>
#include <stb_image.h>



CrossPlatformWindow::CrossPlatformWindow() 
{
    m_Data.width = 1920;
    m_Data.height = 1080; 
}

CrossPlatformWindow::~CrossPlatformWindow() 
{

}

void CrossPlatformWindow::_init() 
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
    s_glfwwindow = window;
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    SetVSync(0);
    glfwSetWindowUserPointer(window, &m_Data);
    stbi_set_flip_vertically_on_load(true);  
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
            if(glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        });
}





float CrossPlatformWindow::CalcDeltaTime() 
{
    
    float CurrentFrame = glfwGetTime();
    m_deltaTime = CurrentFrame - s_window->LastFrame;
    s_window->LastFrame = CurrentFrame;
    return m_deltaTime;
}


//void processInput(GLFWwindow *window )
//{
//    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window,true);
//}




GLFWwindow *CrossPlatformWindow::s_glfwwindow;
CrossPlatformWindow *CrossPlatformWindow::s_window = new CrossPlatformWindow;
float CrossPlatformWindow::m_deltaTime;