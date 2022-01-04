#ifndef __CAMERA2D_H__
#define __CAMERA2D_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "core/Events/Events.h"
#include "core/Events/KeyEvents.h"


class Camera2d 
{
    public:
        Camera2d(float aspectratio); 
        inline const glm::mat4& GetViewProjMatrix() const   { return ViewProjMatrix; };
        inline const glm::mat4& GetViewMatrix() const       { return ViewMatrix; }
        inline const glm::mat4& GetProjMatrix() const       { return ProjMatrix; }
        inline const float& GetRotation() const             { return Rotation; }
        inline void SetPosition(glm::vec3 position)         { Position = position; CalcViewProjMatrix(); } 
        inline void SetRotation(float rotation)             { Rotation = rotation; CalcViewProjMatrix(); }
        inline void ResetProjMatrix(float x, float y)       { ResetProjMatrix(x/y);  }
        inline const float GetZoom() const                  { return ZoomLevel;}
        inline glm::vec3 GetPosition()                      { return Position; }

        inline void ResetProjMatrix(float aspectratio)      
        { 
            ProjMatrix = glm::ortho(-aspectratio*ZoomLevel, aspectratio*ZoomLevel, -ZoomLevel, ZoomLevel); 
            AspectRatio = aspectratio; CalcViewProjMatrix(); 
        }

        inline void ChangeZoomLevel(float offset)          
        { 
            ZoomLevel += offset*(-10);
            if(ZoomLevel <= 1) ZoomLevel = 1; 
            ResetProjMatrix(AspectRatio); 
        }

    private:
        float ZoomLevel = 1;
        float AspectRatio;
        glm::mat4 ViewProjMatrix;
        glm::mat4 ViewMatrix;
        glm::mat4 ProjMatrix;
        glm::vec3 Position;
        float Rotation;
        
        void CalcViewProjMatrix();
};


#endif // __CAMERA2D_H__