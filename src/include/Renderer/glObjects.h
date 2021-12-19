#ifndef GLOBJECTS_H_
#define GLOBJECTS_H_

#include <vector>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glad/glad.h>


#define DE_INT 0x1404
#define DE_UNSIGNED_INT 0x1405
#define DE_FLOAT 0x1406

class vec2 : public glm::vec2
{

};
struct Vertex
{
        glm::vec3 position = {0,0,0};
        glm::vec4 colors = { 0,0,0, 1.0f}; 
        glm::vec2 textCoord = {0,0};
        float textID =  -100; 
        glm::vec3 normal = {0,0,0};

        Vertex();
        //Vertex(aiVector3D& pos);
        Vertex(float _x, float _y);
        Vertex(float _x, float _y, float _z);
        ~Vertex();
        void setPos(float x, float y, float z = 1);
        void setPos(glm::vec3 pos);
        //jvoid setPos(aiVector3D& pos);
        void setCol(float r, float g, float b, float a);
        void setCol(glm::vec3 col, float a = 1.0f);
        void setCol(glm::vec4 col);
        void setTCor(float x, float y);
        void setTCor(glm::vec2 coords);
        //void setTCor(aiVector3D& coords);
        void print();
        void setNormal(float x, float y, float z);
        void setNormal(glm::vec3 norm);
        //void setNormal(aiVector3D& norm);
};

struct Vertex2D
{
    glm::vec3 position;
    glm::vec2 textCoord;
    Vertex2D(Vertex2D& vert)        { position = vert.position; textCoord = vert.textCoord; }
    Vertex2D(glm::vec3 v)           { position = v; textCoord = glm::vec2(0.0f); }
    Vertex2D(){}
    ~Vertex2D() {}
    void SetPosition(glm::vec3 v)   { position = v; }
    void SetTextureCoordinates(glm::vec2 v) { textCoord = v; }
};



struct QuadVertex
{
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TextureCoordinates;
    float TextureID;
};

struct CircleVertex
{
    glm::vec3 Position = { 0.0f, 0.0f, 1.0f };
    glm::vec3 LocalPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec4 Color =    { 1.0f, 1.0f, 1.0f, 1.0f };
    float Thickness = 0.5f;
    float Fade = 0.005;
};







struct QuadData 
{
	glm::vec3 position =	{ 0, 0, 1 };
	glm::vec4 color =		{ 1, 1, 1, 1};
    float rotation = 0;
    glm::vec3 size = { 1.0f, 1.0f, 1.0f };
};





class VertexArray{
        public:
                VertexArray();
                void bind() const       { glBindVertexArray(id);}
                void unbind() const     { glBindVertexArray(0); }
                void newLayout(int nValues, const int nAtt);
                void newLayoutDynamic();
                void Layout2D();
                void QuadLayout();
                void CircleLayout();
                
        private:
                unsigned int id;
                //unsigned int index;
                //size_t offset;
                //int stride;
};

class VertexBuffer
{
        public:
                VertexBuffer();
                VertexBuffer(float vertices[],int size,unsigned int n);
                void bind();
                void bind(float vertices[], int size);
                void unbind() const;
                void bindLayout(VertexArray& vao);
                template<typename T>
                void bindDynamic(int size)
                {
                    glBindBuffer(GL_ARRAY_BUFFER, id);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(T)*size, nullptr, GL_DYNAMIC_DRAW);
                }
                template<typename T>
                void loadDynamic(int offset, size_t size, T*  vertices) { glBufferSubData(GL_ARRAY_BUFFER, offset, size *  sizeof(T), vertices); }
                const uint32_t GetID() const { return id; }
                
        
        private:
                uint32_t id;

};

class ElementBuffer
{
        public:
                ElementBuffer();
                ElementBuffer(uint32_t *indices, int size);
                void bind() const;
                int GetCount() const;
                void set(uint32_t *indices, int size);
                void unbind() const;
                void setDynamic(int offset, int* indices,  int size);
        private:
                unsigned int iCount;
                unsigned int id;
};

struct TextureData
{
        int width, height, nrChannels;
        std::string path;
        unsigned char *data;
};

class Texture
{
        public:
                Texture();
                Texture(int texture_unit, const char* path);
                void bind();
                void active();
                void Set(const char* path,unsigned int texture_unit = 0x84C0);
                void DataSet(unsigned int texture_unit, TextureData* image);
                void SetType(const char* type);
                inline const char* GetPath(){ return FilePath.c_str(); }
                inline void SetTextureID(int texture_unit) { texture_id = texture_unit;}
        private:
                uint32_t id;
                int32_t texture_id = -100;
                std::string FilePath, type;
                void LoadTexture(const char* path);
                void LoadTexturePNG(const char* path);
};


struct aTexture
{
        uint8_t id;
        std::string type;
        std::string path;
};

struct Material
{
                glm::vec3 ambient;
                glm::vec3 diffuse;
                glm::vec3 specular;
                float shininess;
};

namespace texture
{
        void loadText(TextureData* images, std::string path);
}

#endif // GLOBJECTS_H_
