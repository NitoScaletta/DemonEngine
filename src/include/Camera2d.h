#ifndef __CAMERA2D_H__
#define __CAMERA2D_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera2d 
{
    public:
        Camera2d(float left, float right, float down, float top); 
        inline const glm::mat4& GetViewProjMatrix() const   { return ViewProjMatrix; };
        inline const glm::mat4& GetViewMatrix() const       { return ViewMatrix; }
        inline const glm::mat4& GetProjMatrix() const       { return ProjMatrix; }
        inline const float& GetRotation() const             { return Rotation; }
        inline void SetPosition(glm::vec3 position)         { Position = position; CalcViewProjMatrix(); } 
        inline void SetRotation(float rotation)             { Rotation = rotation; CalcViewProjMatrix(); }
        inline void ResetProjMatrix(float left, float right, float bottom, float top) { ProjMatrix = glm::ortho(left,right, bottom, top); }
    private:
        glm::mat4 ViewProjMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;
        glm::vec3 Position;
        float Rotation;
        void CalcViewProjMatrix();
};


#endif // __CAMERA2D_H__