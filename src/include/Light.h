#ifndef LIGHT_H_
#define LIGHT_H_
#include "core.h"
#include "CoreFun.h"
#include "Cube.h"
#include "Camera.h"


class Light : public Cube
{
    public:
        Light();
        ~Light(){};
        glm::vec3 lightColor;
};

class  PhongLight : public Light
{
    public:
                float diffuseInf, ambientInf;
                glm::vec3 diffuseColor, ambientColor, specular;

                PhongLight();
                ~PhongLight();
                virtual void update();
};



class DirectionalLight : public PhongLight
{
        public:
                glm::vec3 direction;

                DirectionalLight();
                ~DirectionalLight(){};
                void SetDir(glm::vec3 dir);

};



class PointLight : public PhongLight
{
        public:
                float constant, linear, quadratic;

                PointLight() : constant(1), linear(1), quadratic(1) {}
                ~PointLight(){};
                void setOptions(float con, float lin, float quadrac);

};


class Flashlight : public PointLight
{

        public:

                float cutOff, fade;
                Camera *camera;
                glm::vec3 direction;

                Flashlight(Camera* cam);
                ~Flashlight(){};

};
#endif // LIGHT_H_
