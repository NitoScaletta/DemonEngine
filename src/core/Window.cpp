#include <core/Window.h>
#include <assert.h>
#include <core/Events/MouseEvents.h>
#include <core/Events/KeyEvents.h>
#include <core/Events/ApplicationEvents.h>
#include <core/Log.h>




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
        DE_ERROR("errore nella creazione della finestra");
        assert(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(m_Data.width, m_Data.height, ApplicationName.c_str(), NULL, NULL);
    if (!window)
    {
        DE_ERROR("Impossibile creare finestra glfw");
        glfwTerminate();
        window = nullptr;
    }
    DE_CORE_INFO("created window {}x{}", static_cast<int>(GetWidth()), static_cast<int>(GetHeight()));
    /* Make the window's context current */
    s_glfwwindow = window;

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
        for(auto& f : data.EventCallback)
            f(event);
        ///glViewport(0,0, x, y);

        }
    );
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event(xpos, ypos);
        for(auto& f : data.EventCallback)
            f(event);
        
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window,double xoffset, double yoffset){
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event(xoffset, yoffset);
        //data.EventCallback(event);
        for(auto& f : data.EventCallback)
            f(event);

    });
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    for(auto& f : data.EventCallback)
                        f(event);
                    //data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
					for(auto& f : data.EventCallback)
						f(event);
                    //data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key,1);  
                    for(auto& f : data.EventCallback)
                        f(event);
                    //data.EventCallback(event);
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



GLFWwindow *CrossPlatformWindow::s_glfwwindow;
CrossPlatformWindow *CrossPlatformWindow::s_window = new CrossPlatformWindow;
float CrossPlatformWindow::m_deltaTime;
std::string CrossPlatformWindow::ApplicationName;