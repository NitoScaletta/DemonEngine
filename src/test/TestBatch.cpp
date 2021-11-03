#include <TestBatch.h>
#include <core/CoreFun.h>
#include <functional>


namespace test{
    TestBatch::TestBatch(Renderer& render, CrossPlatformWindow& mywindow) : renderer(render), m_Window(mywindow)
    {
        nquad = 1;
        prev_nquad = 0;
        vertices = nullptr;
        Texture texture(1, "vc.png");
        vao.bind();
        ebo.bind();
        vbo.bindDynamic(10000000);
        vao.newLayoutDynamic();
        vs.initShader(VertexType::VERTEX);
        fs.initShader(VertexType::FRAGMENT);
        vs.readSourceFile("VertexQuad.glsl");
        fs.readSourceFile("fragment.glsl");
        ps.compileShader(vs.id,fs.id);
        ps.use();
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        ps.setUniMat4f("aMVP", renderer.camera->GetViewProjMatrix());
        m_Window.SetEventCallback(std::bind(&TestBatch::onEvent, this, std::placeholders::_1));
    }



    void TestBatch::onUpdate(float deltatime) 
    {
        VerticesInit(nquad);
        CameraController(deltatime);
        ps.setUniMat4f("aMVP", renderer.camera->GetViewProjMatrix());
        vbo.loadDynamic(0,sizeof(Vertex)*nquad*4, vertices);
        ebo.set(indices.data(), sizeof(int)*indices.size());
    }

    void TestBatch::onRender() 
    {
        renderer.draw(vao,ebo, ps);
    }


    void TestBatch::onImGuiRender() 
    {
        ImGui::SliderInt("nquad", &nquad, 1, 100000);
    }

    void TestBatch::InitVertices(int nquad)
    {
        core::CreateIndices(indices, 1);
        int size = 100;
        vertices = new Vertex[4];
        int x = -50; 
        int y = -50; 
        vertices[0].setPos(x,y);
        vertices[0].setCol(glm::vec4(1.0f));
        vertices[1].setPos(x+size,y);
        vertices[1].setCol(glm::vec4(0.8f,0.3f,0.3f,1.0f));
        vertices[2].setPos(x+size,y+size);
        vertices[2].setCol(glm::vec4(0.3f,0.8f,0.2f, 1.0f));
        vertices[3].setPos(x,y+size);
        vertices[3].setCol(glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
    }

    void TestBatch::VerticesInit(int n)
    {
        if(nquad != prev_nquad)
        {

        
        if(vertices != nullptr)
            delete[] vertices;
        core::CreateIndices(indices, n);
        vertices = new Vertex[n*4];
        int x = 0;
        int y = 0;
        int size = 1;
        int j = 0;
        int offset = 0;
        for (int i = 0; i < n*4; i+=4)
        {
            float color  = ((float)(j%10))/10.0f;
            vertices[i].setPos(x,y);
            vertices[i].setCol(glm::vec4(color));
            vertices[i+1].setPos(x+size,y);
            vertices[i+1].setCol(glm::vec4(color));
            vertices[i+2].setPos(x+size,y+size);
            vertices[i+2].setCol(glm::vec4(color));
            vertices[i+3].setPos(x,y+size);
            vertices[i+3].setCol(glm::vec4(color));
            x+=size + offset;
            j++;
            if(i % 1200 == 0 && i != 0)
            {
                y += size + offset;
                x = 0;
            }
        }
        prev_nquad = nquad;
        }
    }



        void TestBatch::VerticesInitParallel(int n) 
        { 
            if(nquad != prev_nquad)
            {

        
            if(vertices != nullptr)
                delete[] vertices;
            core::CreateIndices(indices, n);
            vertices = new Vertex[n*4];
            int x = -400;
            int y = -400;
            std::future<void> *thr = new std::future<void>[n/4];
            for (int i = 0; i < n*4 - 500; i+=500)
            {
                thr[i] = std::async(std::launch::async, multiloop, vertices, i, x, y, n);
                if(i % 500 == 0 && i != 0)
                {
                    y += 5;
                    x = -500;
                }
                
            }
            prev_nquad = nquad;
            }
        }


        void multiloop(Vertex* vertices, int _i, int x, int y, int n)
        {
            for(int i = _i; i < _i +500  || i +4 >= n; i++)
            {
                vertices[i].setPos(x,y);
                vertices[i+1].setPos(x+5,y);
                vertices[i+1].setCol(0.8f,0.3f,0.3f,1.0f);
                vertices[i+2].setPos(x+5,y+5);
                vertices[i+2].setCol(0.3f,0.8f,0.2f, 1.0f);
                vertices[i+3].setPos(x,y+5);
                vertices[i+3].setCol(0.2f, 0.3f, 0.8f, 1.0f);
            }
        }


    void TestBatch::CameraController(float deltatime) 
    {
        float speed = 1000*deltatime;
        if(glfwGetKey(renderer.GetWindowPointer(), GLFW_KEY_W) == GLFW_PRESS)
            cam_pos.y += speed;
        if(glfwGetKey(renderer.GetWindowPointer(), GLFW_KEY_S) == GLFW_PRESS)
            cam_pos.y -= speed;
        if(glfwGetKey(renderer.GetWindowPointer(), GLFW_KEY_D) == GLFW_PRESS)
            cam_pos.x += speed;
        if(glfwGetKey(renderer.GetWindowPointer(), GLFW_KEY_A) == GLFW_PRESS)
            cam_pos.x -= speed;
        renderer.camera->SetPosition(cam_pos);
    }



    void TestBatch::onEvent(Event& e) 
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&TestBatch::onWindowResizeEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&TestBatch::onMouseScrollEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&TestBatch::onKeyPressedEvent, this, std::placeholders::_1));

       
    }

    bool TestBatch::onWindowResizeEvent(WindowResizeEvent& e) 
    {
        renderer.camera->ResetProjMatrix(e.GetWidth(), e.GetHeight());
        return true;
    }

    bool TestBatch::onMouseScrollEvent(MouseScrolledEvent& e) 
    {
        renderer.camera->ChangeZoomLevel(e.GetYoffset());
        return true;
    }


    bool TestBatch::onKeyPressedEvent(KeyPressedEvent& e) 
    {
        return true;
    }

}