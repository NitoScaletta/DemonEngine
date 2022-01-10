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



struct QuadVertex
{
    glm::vec3 Position              = { 0.0f, 0.0f, 0.0f };
    glm::vec4 Color                 = { 1.0f, 1.0f, 1.0f, 1.0f };
    glm::vec2 TextureCoordinates;
    float TextureID                 = 0;
    float TilingFactor              = 1;
};

struct CircleVertex
{
    glm::vec3 Position      = { 0.0f, 0.0f, 0.0f };
    glm::vec3 LocalPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec4 Color         = { 1.0f, 1.0f, 1.0f, 1.0f };
    float Thickness         = 0.5f;
    float Fade              = 0.005;
};

struct QuadData 
{
	glm::vec3 position      = { 0, 0, 0 };
	glm::vec4 color         = { 1, 1, 1, 1};
    float rotation          = 0;
    glm::vec3 size          = { 1.0f, 1.0f, 1.0f };
    float TextureSlotIndex  = 0;
};





class VertexArray{
        public:
                VertexArray();
                void bind() const       { glBindVertexArray(id);}
                void unbind() const     { glBindVertexArray(0); }
                void newLayout(int nValues, const int nAtt);
                void QuadLayout();
                void CircleLayout();
                
        private:
                unsigned int id;
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
                void set(uint32_t *indices, size_t size);
                void unbind() const;
                void setDynamic(int offset, int* indices,  int size);
        private:
                unsigned int iCount;
                unsigned int id;
};


class Texture
{
        public:
                Texture() {}
                Texture(uint32_t width, uint32_t height, void* data);
                Texture(const char* path);
                void bindSlot(uint32_t _slot) { glBindTextureUnit(_slot, id); slot = _slot; };
                int32_t GetTextureSlot() { return slot; }
                uint32_t GetWidth() { return m_width; }
                uint32_t GetHeight() { return m_height; }
                size_t GetChannelsNumber() { return ChannelNumber; }
                uint32_t GetID() { return id; }
        private:
                uint32_t id = 0;
                int32_t slot = -100;
                uint32_t m_width = 1, m_height = 1;
                size_t ChannelNumber = 0;
};


class SubTexture
{
public:
    SubTexture() {};
    SubTexture(std::shared_ptr<Texture> texture,  const uint32_t x, uint32_t y, const uint32_t width, const uint32_t height);
    ~SubTexture() {}
    void GetTextureCoords(glm::vec2* textcoords) const;
    void ChangeTile(uint32_t x, uint32_t y) { TileCoords.x = x; TileCoords.y = y; }
    void ChangeTile(glm::vec2 coords) { TileCoords = coords; }
    const float GetTextureID() const { return m_Texture->GetTextureSlot(); }
    std::shared_ptr<Texture> GetTexture() { return m_Texture;  }


private:
    uint32_t tile_height = 0, tile_width = 0;
    glm::vec2 TileCoords = {0,0};
    std::shared_ptr<Texture>  m_Texture;

};


#endif // GLOBJECTS_H_
