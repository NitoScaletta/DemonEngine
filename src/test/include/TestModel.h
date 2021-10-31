#ifndef __TESTMODEL_H__
#define __TESTMODEL_H__

#include <test.h>
#include <meshes/Mesh.h>
#include<Renderer/Camera.h>

namespace test
{
class TestModel : public Test
{
    public:

        TestModel(Camera* camera);
        ~TestModel(){};

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
        
    private:
        Model* model;
        glm::mat4 model_mat, proj, view;
        Camera* camera;

}; 

}
#endif // __TESTMODEL_H_