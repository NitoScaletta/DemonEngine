#include "Cube.h"
#include "CoreFun.h"
#include "Light.h"

Cube::~Cube(){}
Cube::Cube(const char* vertexshader)
{
    name = "cube";
    std::vector<int> indices;
    core::CreateIndices(indices, 6);
    core::createVerticesCube(vertices );
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(), sizeof(int)*indices.size());
    vbo.bindDynamic(100);
    vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
    vao.newLayoutDynamic();
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile(vertexshader);
    ps.compileShader(vs.id, fs.id);
    Model = glm::mat4(0.0f);
    material.shininess = 32.0f;
}

void Shape::SetPos(float x, float y, float z)
{
    pos = glm::vec3(x,y,z);
    Model =  glm::translate(glm::mat4(1.0f), pos);
}

void Shape::SetTexture(unsigned int texture_id)
{
    ps.setUnifi("texture1", texture_id);
}


void Shape::SetDiffuseMap(unsigned int texture_id)
{
    ps.setUnifi("material.diffuse", texture_id);
}

void Shape::SetSpecularMap(unsigned int texture_id)
{
    ps.setUnifi("material.specular", texture_id);
}

glm::mat4 Shape::model()
{
    Model = glm::scale(glm::mat4(1.0f), scale);
    Model = glm::translate(glm::mat4(1.0f), pos);
    return Model;
}

void Cube::SetScale(float Scale)
{
    scale = glm::vec3(Scale);
}

void Shape::UpdateMVP(glm::mat4 proj,glm::mat4 view){
    glm::mat4  mvp = proj * view * model();
    ps.setUniMat4f("aMVP", mvp);

}

void Shape::setUniMaterial(glm::vec3 lightColor, glm::vec3 spec)
{
        ps.setUniff  ("material.shininess", material.shininess);
        ps.setUniVec3("material.specular",  spec);
}

void Shape::setUniLight(PhongLight* light)
{
            light->update();
            ps.setUniVec3("light.ambient",  light->ambientColor);
            ps.setUniVec3("light.diffuse",  light->diffuseColor);
            ps.setUniVec3("light.position", light->pos);
            ps.setUniVec3("light.specular", light->specular );
}

void Shape::setUniDirLight(DirectionalLight* light)
{
            light->update();
            ps.setUniVec3("light.ambient",  light->ambientColor);
            ps.setUniVec3("light.diffuse",  light->diffuseColor);
            ps.setUniVec3("light.direction", light->direction);
            ps.setUniVec3("light.specular", light->specular );
}


void Shape::setUniPointLight(PointLight* light)
{
            light->update();
            ps.setUniVec3("light.position", light->pos);
            ps.setUniVec3("light.ambient",  light->ambientColor);
            ps.setUniVec3("light.diffuse",  light->diffuseColor);
            ps.setUniVec3("light.specular", light->specular );
            ps.setUniff("light.constant", light->constant);
            ps.setUniff("light.linear", light->linear);
            ps.setUniff("light.quadratic", light->quadratic);
}


void Shape::setUniFlashlight(Flashlight* light)
{
    light->direction = light->camera->cameraFront;
    light->pos = light->camera->cameraPosition;
    light->update();
    ps.setUniVec3("light.position", light->pos);
    ps.setUniVec3("light.ambient",  light->ambientColor);
    ps.setUniVec3("light.diffuse",  light->diffuseColor);
    ps.setUniVec3("light.specular", light->specular );
    ps.setUniff("light.constant", light->constant);
    ps.setUniff("light.linear", light->linear);
    ps.setUniff("light.quadratic", light->quadratic);
    ps.setUniVec3("light.direction", light->direction);
    ps.setUniff("light.cutoff", glm::cos(glm::radians(light->cutOff)));
    ps.setUniff("light.cutoffouter", glm::cos(glm::radians(light->cutOff+light->fade)));
}

void Cube::unbind()
{
    vao.unbind();
    ebo.unbind();
    vbo.unbind();
}


void Shape::draw(Renderer* rend)
{
    if(shouldbeDraw)
        rend->draw(vao, ebo, ps);
}




Plane::Plane()
{
    name = "plane";
    std::vector<int> indices;
    core::CreateIndices(indices, 1);
    CreateBuffer();
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(), sizeof(int)*indices.size());
    vbo.bindDynamic(10);
    vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
    vao.newLayoutDynamic();
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile("fragmentDiffuse.txt");
    ps.compileShader(vs.id, fs.id);
    Model = glm::mat4(1.0f);
    material.shininess = 32.0f;
}


void Plane::CreateBuffer()
{
    vertices.push_back(Vertex(-10, 0, -10));
    vertices.back().setTCor(0, 0);
    vertices.back().setNormal(0, 1, 0);
    vertices.push_back(Vertex(10, 0, -10));
    vertices.back().setTCor(1, 0);
    vertices.back().setNormal(0, 1, 0);
    vertices.push_back(Vertex(10, 0, 10));
    vertices.back().setTCor(1, 1);
    vertices.back().setNormal(0, 1, 0);
    vertices.push_back(Vertex(-10, 0, 10));
    vertices.back().setTCor(0, 1);
    vertices.back().setNormal(0, 1, 0);
}
