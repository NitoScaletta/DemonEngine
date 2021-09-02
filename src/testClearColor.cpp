#include "include/testClearColor.h"
#include "glad/glad.h"
#include "imgui/imgui.h"

test::TestClearColor::TestClearColor()
    : m_Color{ 0.9f, 0.3f, 0.2f, 1.0f}
{

}
test::TestClearColor::~TestClearColor(){

}
void test::TestClearColor::onUpdate(float deltatime){

}
void test::TestClearColor::onRender(){
        glClearColor(m_Color[0],m_Color[1],m_Color[2],m_Color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
}
void test::TestClearColor::onImGuiRender(){

            ImGui::ColorEdit4("Clear Color", m_Color);

}
