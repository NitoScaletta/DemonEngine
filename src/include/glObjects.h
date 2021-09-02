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
                unsigned int id;
                unsigned int index;
                unsigned int offset;
                int stride;
                VertexArray();
                void bind() const;
                void unbind() const;
                void newLayout(int nValues, const int& nAtt);
                void newLayoutDynamic();
};

class VertexBuffer
{
        public:
                unsigned int natt;//number of attributes
                unsigned int id;
                VertexBuffer();
                VertexBuffer(float vertices[],int size,unsigned int n);
                void bind();
                void bind(float vertices[], int size);
                void unbind() const;
                void bindLayout(VertexArray& vao);
                void bindDynamic(int size);
                void loadDynamic(int offset, int size, Vertex*  vertices);
};

class ElementBuffer
{
        public:
                unsigned int id;
                ElementBuffer();
                ElementBuffer(int *indices, int size);
                void bind() const;
                int GetCount() const;
                void set(int *indices, int size);
                void unbind() const;
                void setDynamic(int offset, int size, int* indices);
        private:
                unsigned int iCount;
};

class Texture
{
        public:
                unsigned int id;
                unsigned char *data;
                int width, height, nrChannels;
                int texture_id;
                Texture();
                Texture(int texture_unit, const char* path);
                void bind();
                void active();
                void Set(const char* path,unsigned int texture_unit);
                void LoadImage(const char* path);
                void LoadImagePNG(const char* path);
};


class Material
{
        public:
                glm::vec3 ambient;
                glm::vec3 diffuse;
                glm::vec3 specular;
                float shininess;
};


#endif // GLOBJECTS_H_
