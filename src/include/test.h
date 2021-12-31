#ifndef TEST_H_
#define TEST_H_
#include "core/Events/Events.h"

namespace test{

    class Test{
        public:
            Test(){};
            virtual ~Test(){};

            virtual void onUpdate(float deltatime) = 0;
            virtual void onRender() = 0;
            virtual void onImGuiRender() = 0;
            virtual void onEvent(Event& e) = 0;

    };
}


#endif // TEST_H_
