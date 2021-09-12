#include "Cube.h"
#include "CoreFun.h"
#include "Light.h"


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
    return Model;
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

void Shape::UpdateMVP(glm::mat4 proj,glm::mat4 view){
    glm::mat4  mvp = proj * view * Model;
    ps.setUniMat4f("aMVP", mvp);
}


void Shape::draw(Renderer* rend)
{
    if(shouldbeDraw)
        rend->draw(vao, ebo, ps);
}

void Shape::setCameraPosition(Camera* camera)
{
    ps.setUniVec3("viewPos", camera->cameraPosition);
}


void Shape::setUniModel()
{
    ps.setUniMat4f("model", Model);
}

void readfile(Shader* shader, std::string str)
{
    shader->readSourceFile(str.c_str());
}


Cube::~Cube(){}
Cube::Cube(const char* fragmentshader)
{
    name = "cube";
    std::vector<int> indices;
    core::CreateIndices(indices, 6);
    CreateBuffer();
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(), sizeof(int)*indices.size());
    vbo.bindDynamic(24);
    vbo.loadDynamic(0, sizeof(vertArr), vertArr);
    vao.newLayoutDynamic();
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile(fragmentshader);
    ps.compileShader(vs.id, fs.id);
    Model = glm::mat4(0.0f);
    material.shininess = 32.0f;
}


void Cube::CreateBuffer()
{
    //Timer  timer("array static");
    vertArr[0].setPos(-0.5f, -0.5f , -0.5f);
    vertArr[0].setTCor(0, 0);
    vertArr[0].setNormal(0, 0, -1);
    vertArr[1].setPos(0.5f, -0.5f , -0.5f);
    vertArr[1].setTCor(1, 0);
    vertArr[1].setNormal(0, 0, -1);
    vertArr[2].setPos(0.5f, 0.5f , -0.5f);
    vertArr[2].setTCor(1, 1);
    vertArr[2].setNormal(0, 0, -1);
    vertArr[3].setPos(-0.5f, 0.5f , -0.5f);
    vertArr[3].setTCor(0, 1);
    vertArr[3].setNormal(0, 0, -1);

    vertArr[4].setPos(-0.5f, -0.5f , 0.5f);
    vertArr[4].setTCor(0, 0);
    vertArr[4].setNormal(0, 0, 1);
    vertArr[5].setPos(0.5f, -0.5f , 0.5f);
    vertArr[5].setTCor(1, 0);
    vertArr[5].setNormal(0, 0, 1);
    vertArr[6].setPos(0.5f, 0.5f , 0.5f);
    vertArr[6].setTCor(1, 1);
    vertArr[6].setNormal(0, 0, 1);
    vertArr[7].setPos(-0.5f, 0.5f , 0.5f);
    vertArr[7].setTCor(0, 1);
    vertArr[7].setNormal(0, 0, 1);


    vertArr[8].setPos(-0.5f, -0.5f , -0.5f);
    vertArr[8].setTCor(0, 0);
    vertArr[8].setNormal(0, -1, 0);
    vertArr[9].setPos(0.5f, -0.5f , -0.5f);
    vertArr[9].setTCor(1, 0);
    vertArr[9].setNormal(0, -1, 0);
    vertArr[10].setPos(0.5f, -0.5f , 0.5f);
    vertArr[10].setTCor(1, 1);
    vertArr[10].setNormal(0, -1, 0);
    vertArr[11].setPos(-0.5f, -0.5f , 0.5f);
    vertArr[11].setTCor(0, 1);
    vertArr[11].setNormal(0, -1, 0);


    vertArr[12].setPos(-0.5f, 0.5f , -0.5f);
    vertArr[12].setTCor(0, 0);
    vertArr[12].setNormal(0, 1, 0);
    vertArr[13].setPos(0.5f, 0.5f , -0.5f);
    vertArr[13].setTCor(1, 0);
    vertArr[13].setNormal(0, 1, 0);
    vertArr[14].setPos(0.5f, 0.5f , 0.5f);
    vertArr[14].setTCor(1, 1);
    vertArr[14].setNormal(0, 1, 0);
    vertArr[15].setPos(-0.5f, 0.5f , 0.5f);
    vertArr[15].setTCor(0, 1);
    vertArr[15].setNormal(0, 1, 0);


    vertArr[16].setPos(0.5f, -0.5f , -0.5f);
    vertArr[16].setTCor(0, 0);
    vertArr[16].setNormal(1, 0, 0);
    vertArr[17].setPos(0.5f, -0.5f , 0.5f);
    vertArr[17].setTCor(1, 0);
    vertArr[17].setNormal(1, 0, 0);
    vertArr[18].setPos(0.5f, 0.5f , 0.5f);
    vertArr[18].setTCor(1, 1);
    vertArr[18].setNormal(1, 0, 0);
    vertArr[19].setPos(0.5f, 0.5f , -0.5f);
    vertArr[19].setTCor(0, 1);
    vertArr[19].setNormal(1, 0, 0);


    vertArr[20].setPos(-0.5f, -0.5f , -0.5f);
    vertArr[20].setTCor(0, 0);
    vertArr[20].setNormal(-1, 0, 0);
    vertArr[21].setPos(-0.5f, -0.5f , 0.5f);
    vertArr[21].setTCor(1, 0);
    vertArr[21].setNormal(-1, 0, 0);
    vertArr[22].setPos(-0.5f, 0.5f , 0.5f);
    vertArr[22].setTCor(1, 1);
    vertArr[22].setNormal(-1, 0, 0);
    vertArr[23].setPos(-0.5f, 0.5f , -0.5f);
    vertArr[23].setTCor(0, 1);
    vertArr[23].setNormal(-1, 0, 0);



}



void Shape::SetScale(float Scale)
{
    scale = glm::vec3(Scale);
    Model = glm::scale(Model, scale);
}

void Cube::unbind()
{
    vao.unbind();
    ebo.unbind();
    vbo.unbind();
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
