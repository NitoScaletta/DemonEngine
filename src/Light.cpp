#include "Light.h"



Light::Light() : Cube(),
                 lightColor(glm::vec3(1.0f))
{
    std::vector<int> indices;
    core::CreateIndices(indices, 6);
    core::createVerticesCube(vertices);
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(), sizeof(int)*indices.size());
    vbo.bindDynamic(100);
    vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
    vao.newLayoutDynamic();
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile("fragmentLight.txt");
    ps.compileShader(vs.id, fs.id);
    ps.setUniVec3("aColor", lightColor);
    Model = glm::mat4(1.0f);
}




PhongLight::PhongLight() : ambientInf(1.0f),
                           diffuseInf(0.5f),
                           specular(glm::vec3(1.0f))
{

    diffuseColor = lightColor * diffuseInf;
    ambientColor = lightColor * ambientInf;
}




PhongLight::~PhongLight(){

}

void PhongLight::update()
{
    diffuseColor = lightColor * diffuseInf;
    ambientColor = lightColor * ambientInf;
}

DirectionalLight::DirectionalLight() : direction(glm::vec3(1.0f)) {}


void DirectionalLight::SetDir(glm::vec3 dir)
{
    direction = dir;
}


void PointLight::setOptions(float con, float lin, float quadra)
{
    constant = con;
    linear = lin;
    quadratic = quadra;
}


Flashlight::Flashlight(Camera* cam) : camera(cam),
                                      fade(2.0f)
{
    shouldbeDraw = false;
}
