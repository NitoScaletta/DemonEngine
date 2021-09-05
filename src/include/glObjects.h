#ifndef GLOBJECTS_H_
#define GLOBJECTS_H_

#include <vector>
#include  <iostream>
#include "stb_image.h"
#include "glm/glm.hpp"

struct Vertex
{
        float positions[3];
        float colors [4];
        float textCoord[2];
        float textID;
        float normal[3];

        Vertex();
        Vertex(float _x, float _y);
        Vertex(float _x, float _y, float _z);
        ~Vertex();
        void setPos(float x, float y, float z);
        void setCol(float r, float g, float b, float a);
        void setTCor(float x, float y);
        void print();
        void setNormal(float x, float y, float z);
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
                void DataSet(const char* path,unsigned int texture_unit, TextureData* image);
        private:
                unsigned int id;
                unsigned char *data;
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
