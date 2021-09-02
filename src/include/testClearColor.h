#ifndef TESTCLEARCOLOR_H_
#define TESTCLEARCOLOR_H_
#include "test.h"
namespace test{

    class TestClearColor : public Test
    {
        public:
            TestClearColor();
            ~TestClearColor();
            void onUpdate(float deltatime) override;
            void onRender() override;
            void onImGuiRender() override;
        private:
            float m_Color[4];

    };

};


#endif // TESTCLEARCOLOR_H_
