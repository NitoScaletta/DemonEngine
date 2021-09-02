#ifndef TEST_H_
#define TEST_H_
#include "glObjects.h"
#include "Shader.h"

namespace test{

    class Test{
        public:
            Test(){};
            virtual ~Test(){};
            //VertexArray vao;
            //VertexBuffer  vbo;
            //ElementBuffer  ebo;
            //Shader vs;
            //Shader fs;
            //ShaderProgram ps;

            virtual void onUpdate(float deltatime) {}
            virtual void onRender() {}
            virtual void onImGuiRender() {}
    };
}


#endif // TEST_H_
