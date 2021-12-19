#include <core/CoreFun.h>
#include "Renderer/glObjects.h"
#include "glad/glad.h"
#include "core/profiling/Timer.h"
#include "core/Log.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &id);

}

VertexBuffer::VertexBuffer(float vertices[], int size, unsigned int n)
{
    glGenBuffers(1, &id);
    bind(vertices, size);
}

void VertexBuffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, id);
}
void VertexBuffer::bind(float vertices[], int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::bindLayout(VertexArray& vao)
{
    vao.newLayout(3,10);
    vao.newLayout(4,10);
    vao.newLayout(2,10);
    vao.newLayout(1,10);
}

VertexArray::VertexArray() 
{
    glGenVertexArrays(1, &id);
}

void VertexArray::newLayout(int nValues, const int nAtt)
{
    }

void VertexArray::newLayoutDynamic()
{
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float)*13, 0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE,sizeof(float)*13, (const void*)offsetof(Vertex, colors));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE,sizeof(float)*13, (const void*)offsetof(Vertex,textCoord));
   glEnableVertexAttribArray(3);
   glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE,sizeof(float)*13, (const void*)offsetof(Vertex,textID));
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(4,3, GL_FLOAT, GL_FALSE,sizeof(float)*13, (const void*)offsetof(Vertex,normal));
}


void VertexArray::Layout2D()
{
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float)*5, 0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE,sizeof(float)*5, (const void*)offsetof(Vertex2D, textCoord));
}


void VertexArray::QuadLayout()
{
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float)*10, 0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE,sizeof(float)*10, (const void*)offsetof(QuadVertex, Color));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE,sizeof(float)*10, (const void*)offsetof(QuadVertex, TextureCoordinates));
   glEnableVertexAttribArray(3);
   glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE,sizeof(float)*10, (const void*)offsetof(QuadVertex, TextureID));
}


void VertexArray::CircleLayout()
{

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float)*12, 0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,sizeof(float)*12, (const void*)offsetof(CircleVertex, LocalPosition));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2,4, GL_FLOAT, GL_FALSE,sizeof(float)*12, (const void*)offsetof(CircleVertex, Color));
   glEnableVertexAttribArray(3);
   glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE,sizeof(float)*12, (const void*)offsetof(CircleVertex, Thickness));
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(4,1, GL_FLOAT, GL_FALSE,sizeof(float)*12, (const void*)offsetof(CircleVertex, Fade));
}



ElementBuffer::ElementBuffer()  : iCount(0)
{
    glGenBuffers(1,&id);
}

ElementBuffer::ElementBuffer(uint32_t *indices, int size)
{
    glGenBuffers(1,&id);
    bind();
    set(indices,size);
}

int ElementBuffer::GetCount() const
{
    return iCount;
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ElementBuffer::set(uint32_t *indices, int size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}


void ElementBuffer::setDynamic(int offset, int* indices, int size)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
}

Texture::Texture()  
{
    glGenTextures(1, &id);
}

Texture::Texture(int texture_unit, const char* path)
{
    glGenTextures(1, &id);
    Set(path, texture_unit);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::active()
{
    glActiveTexture(texture_id);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Set(const char* path, unsigned int texture_unit)
{
    texture_id = texture_unit;
    FilePath = path;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::string file = path;
    if(path[file.length()-3] == 'p')
    {
        LoadTexturePNG(path);
    }
    else
    {
        LoadTexture(path);
    }
}


void Texture::LoadTexture(const char* path)
{
    int32_t width, height, nrChannels;
    char completePath[100] = "res/textures/";
    strncat(completePath, path, 99);
    unsigned char* data = stbi_load(completePath, &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else{
        DE_CORE_WARNING("{0} not found", path);
    }
}

void Texture::LoadTexturePNG(const char* path)
{
    int32_t width, height, nrChannels;
    char completePath[100] = "res/textures/";
    strncat(completePath, path, 99);
    unsigned char* data = stbi_load(completePath, &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else{
        DE_CORE_WARNING("{0} not found", path);
    }
}

void Texture::DataSet( unsigned int texture_unit, TextureData* image)
{
    texture_id = texture_unit;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::string file = image->path;
    if (image){
            if(file[file.length()-3] == 'p')
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(image->data);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height,
                             0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(image->data);
            }
    }
    else DE_CORE_WARNING("data not found");
}

void Texture::SetType(const char* typ) 
{
    type = typ;
}


Vertex::Vertex()
{
}


Vertex::Vertex(float _x, float _y)
{
        setPos( _x, _y, 0.0f);
        setCol(1.0f, 0.0f, 0.0f, 1.0f);
        setTCor(1.0f, 1.0f);
        textID = 0.0f;
}


Vertex::Vertex(float _x, float _y, float _z)
{
        setPos( _x, _y, _z);
        setCol(1.0f, 0.0f, 0.0f, 1.0f);
        setTCor(1.0f, 1.0f);
        textID = 0.0f;
}


Vertex::~Vertex(){

}

void Vertex::setPos(float x, float y, float z){
    position.x = x;
    position.y = y;
    position.z = z;
}

void Vertex::setPos(glm::vec3 pos)
{
    position = pos;
}

void Vertex::setCol(float r, float g, float b, float a){
    colors.x = r;
    colors.y = g;
    colors.z = b;
    colors.w = a;
}

void Vertex::setCol(glm::vec3 col, float a)
{
    colors = glm::vec4(col,a);
}


void Vertex::setCol(glm::vec4 col)
{
    colors = col;
}

void Vertex::setTCor(float x, float y){
    textCoord.x = x;
    textCoord.y = y;
}


void Vertex::setTCor(glm::vec2 tcoo)
{
    textCoord =  tcoo;
}


void Vertex::print()
{
    DE_CORE_TRACE("position   x = {0}, y = {1} z = {2}", position.x, position.y, position.z);
    DE_CORE_TRACE("normal     x = {0}, y = {1} z = {2}", normal.x, normal.y, normal.z);
    DE_CORE_TRACE("color      r = {0}, g = {1} b = {2}, a = {3}", colors.x, colors.y, colors.z);
}

void Vertex::setNormal(float x, float y, float z)
{
    normal.x = x;
    normal.y = y;
    normal.z = z;
}
void Vertex::setNormal(glm::vec3 norm)
{
    normal = norm;
}

namespace texture
{
void loadText(TextureData* images, std::string path)
    {
        images->data = stbi_load(path.c_str(), &images->width, &images->height,
                                 &images->nrChannels, 0);
        images->path = path;
    }

}
