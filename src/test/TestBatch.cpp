#include <TestBatch.h>
#include <core/CoreFun.h>
#include <core/Input.h>


namespace test{
    TestBatch::TestBatch() 
    {
        camera = new Camera2d(16.f/9.f);
        nquad = 1;
        prev_nquad = 0;
        vertices = nullptr;
        Texture texture(1, "vc.png");
        vao.bind();
        ebo.bind();
        vbo.bindDynamic(10000000);
        vao.newLayoutDynamic();
        vs.initShader(VERTEX_SHADER);
        fs.initShader(FRAGMENT_SHADER);
        vs.readSourceFile("VertexQuad.glsl");
        fs.readSourceFile("fragment.glsl");
        ps.compileShader(vs.id,fs.id);
        ps.use();
        model = glm::mat4(1.0f);
        view = glm::mat4(1.0f);
        ps.setUniMat4f("aMVP", camera->GetViewProjMatrix());
        CrossPlatformWindow::SetEventCallBack(BIND_EVENT(TestBatch::onEvent));
    }



    void TestBatch::onUpdate(float deltatime) 
    {
        CameraController(deltatime);
        ps.setUniMat4f("aMVP", camera->GetViewProjMatrix());
        if(nquad != prev_nquad)
        {
            VerticesInit(nquad);
            vbo.loadDynamic(0,sizeof(Vertex)*nquad*4, vertices);
            ebo.set(indices.data(), sizeof(int)*indices.size());
        }
    }

    void TestBatch::onRender() 
    {
        Renderer::draw(vao,ebo, ps);
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
        if(Input::isPressed(Key::W))
            cam_pos.y += speed;
        if(Input::isPressed(Key::S))
            cam_pos.y -= speed;
        if(Input::isPressed(Key::D))
            cam_pos.x += speed;
        if(Input::isPressed(Key::A))
            cam_pos.x -= speed;
        camera->SetPosition(cam_pos);
    }



    void TestBatch::onEvent(Event& e) 
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(TestBatch::onWindowResizeEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT(TestBatch::onMouseScrollEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(TestBatch::onKeyPressedEvent));
    }

    bool TestBatch::onWindowResizeEvent(WindowResizeEvent& e) 
    {
        camera->ResetProjMatrix(e.GetWidth(), e.GetHeight());
        return true;
    }

    bool TestBatch::onMouseScrollEvent(MouseScrolledEvent& e) 
    {
        camera->ChangeZoomLevel(e.GetYoffset());
        return true;
    }


    bool TestBatch::onKeyPressedEvent(KeyPressedEvent& e) 
    {
        core::msg(e.toString().c_str());
        return true;
    }

}