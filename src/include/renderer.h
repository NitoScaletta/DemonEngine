#ifndef RENDERER_H_
#define RENDERER_H_
class VertexArray;
class ShaderProgram;
class ElementBuffer;
class GLFWwindow;

class Renderer
{
    public:
        GLFWwindow* wind;
        void draw(VertexArray& vao, ElementBuffer& ebo, ShaderProgram& ps);
        void init();
        GLFWwindow* createWindow(unsigned int x,unsigned int y);
        void update();
};

#endif // RENDERER_H_
