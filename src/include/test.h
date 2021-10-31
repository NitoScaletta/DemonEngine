#ifndef TEST_H_
#define TEST_H_
#include "graphic/glObjects.h"
#include "graphic/Shader.h"

namespace test{

    class Test{
        public:
            Test(){};
            virtual ~Test(){};

            virtual void onUpdate(float deltatime) {}
            virtual void onRender() {}
            virtual void onImGuiRender() {}
    };
}


#endif // TEST_H_
