#ifndef GLOBJECTS_H_
#define GLOBJECTS_H_

#include <vector>
#include  <iostream>
#include "stb_image.h"
#include "glm/glm.hpp"

struct Vertex
{
        glm::vec3 position;
        glm::vec4 colors;
        glm::vec2 textCoord;
        float textID;
        glm::vec3 normal;

        Vertex();
        Vertex(float _x, float _y);
        Vertex(float _x, float _y, float _z);
        ~Vertex();
        void setPos(float x, float y, float z);
        void setPos(glm::vec3 pos);
        void setCol(float r, float g, float b, float a);
        void setCol(glm::vec3 col, float a = 1.0f);
        void setCol(glm::vec4 col);
        void setTCor(float x, float y);
        void setTCor(glm::vec2 coords);
        void print();
        void setNormal(float x, float y, float z);
        void setNormal(glm::vec3 norm);
};

class VertexArray{
        public:
                VertexArray();
                void bind() const;
                void unbind() const;
                void newLayout(int nValues, const int& nAtt);
                void newLayoutDynamic();
        private:
                unsigned int id;
                unsigned int index;
                unsigned int offset;
                int stride;
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
                void bindDynamic(int size);
                void loadDynamic(int offset, int size, Vertex*  vertices);
        private:
                unsigned int natt;//number of attributes
                unsigned int id;

};

class ElementBuffer
{
        public:
                ElementBuffer();
                ElementBuffer(int *indices, int size);
                void bind() const;
                int GetCount() const;
                void set(int *indices, int size);
                void unbind() const;
                void setDynamic(int offset, int size, int* indices);
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
                void Set(const char* path,unsigned int texture_unit);
                void DataSet(unsigned int texture_unit, TextureData* image);
        private:
                unsigned int id;
                int width, height, nrChannels;
                int texture_id;
                void LoadImage(const char* path);
                void LoadImagePNG(const char* path);
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
