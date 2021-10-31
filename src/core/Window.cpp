#include <core/Window.h>
#include <assert.h>

WindowsWindow::WindowsWindow() 
{
    x = 1280;
    y = 720;
}

WindowsWindow::~WindowsWindow() 
{

}

void WindowsWindow::init() 
{
    if (!glfwInit())
    {
        std::cout << "errore nella creazione della finestra" << std::endl;
        assert(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(x, y, "DemonEngine", NULL, NULL);
    if (!window)
    {
        std::cout << "Impossibile creare finestra glfw" << std::endl;
        glfwTerminate();
        window = nullptr;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int x, int y){
        glViewport(0, 0, x, y);
        std::cout <<  "new res set to:  x) " << x << "y) " << y  << std::endl;
    } );
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos){
        std::cout << "MousePos: x) " << xpos << " y) " << ypos << std::endl; 
    });
    glfwSetScrollCallback(window, [](GLFWwindow *window,double xoffset, double yoffset){
        std::cout << "scroll "<< yoffset;
    });
}



