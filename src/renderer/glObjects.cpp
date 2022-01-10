#include "core/Log.h"
#include <core/CoreFun.h>
#include "Renderer/glObjects.h"
#include "glad/glad.h"
#include "core/profiling/Timer.h"

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





void VertexArray::QuadLayout()
{
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,sizeof(float)*11, 0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE,sizeof(float)*11, (const void*)offsetof(QuadVertex, Color));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE,sizeof(float)*11, (const void*)offsetof(QuadVertex, TextureCoordinates));
   glEnableVertexAttribArray(3);
   glVertexAttribPointer(3,1, GL_FLOAT, GL_FALSE,sizeof(float)*11, (const void*)offsetof(QuadVertex, TextureID));
   glEnableVertexAttribArray(4);
   glVertexAttribPointer(4,1, GL_FLOAT, GL_FALSE,sizeof(float)*11, (const void*)offsetof(QuadVertex, TilingFactor));
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

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////  ELEMENT BUFFER //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

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


void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ElementBuffer::set(uint32_t *indices, size_t size)
{
    size = sizeof(uint32_t) * size;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
}


void ElementBuffer::setDynamic(int offset, int* indices, int size)
{
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, indices);
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////    TEXTURES /////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


Texture::Texture(uint32_t width, uint32_t height, void* data)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
    glTextureStorage2D(id, 1, GL_RGBA8, width, height);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    ChannelNumber = 4;
    glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

Texture::Texture(const char* path) 
{
    glCreateTextures(GL_TEXTURE_2D, 1, &id);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    stbi_set_flip_vertically_on_load(true); 
    int32_t width, height, nrChannels;
    char completePath[100] = "res/textures/";
    strncat(completePath, path, 99);
    unsigned char* data = stbi_load(completePath, &width, &height, &nrChannels, 0);
    m_width = width;
    m_height = height;
    ChannelNumber = nrChannels;
    if (data)
    {
        if (nrChannels == 4)
        {
        	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
        	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 3)
        {
        	glTextureStorage2D(id, 1, GL_RGB8, width, height);
        	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        DE_CORE_TRACE("Loaded {} with {} channels, {}x{}", completePath, nrChannels, width, height);
	    stbi_image_free(data);
       
    }
    else
    {
        DE_CORE_ERROR("Texture {} not found", completePath);
    }


}



SubTexture::SubTexture(std::shared_ptr<Texture> texture, const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) 
    : tile_width(width), tile_height(height), m_Texture(texture), TileCoords(glm::vec2(x,y))
{
}


void SubTexture::GetTextureCoords(glm::vec2* textcoords) const
{
    textcoords[0].x = (TileCoords.x * tile_width ) / m_Texture->GetWidth();
    textcoords[0].y = (TileCoords.y * tile_height) / m_Texture->GetHeight();
    textcoords[1].x = ((TileCoords.x + 1) * tile_width )/ m_Texture->GetWidth();
    textcoords[1].y = (TileCoords.y  * tile_height)/ m_Texture->GetHeight();
    textcoords[2].x = ((TileCoords.x + 1) * tile_width )/ m_Texture->GetWidth();
    textcoords[2].y = ((TileCoords.y + 1) * tile_height)/ m_Texture->GetHeight();
    textcoords[3].x = (TileCoords.x * tile_width ) / m_Texture->GetWidth();
    textcoords[3].y = ((TileCoords.y + 1) * tile_height)/ m_Texture->GetHeight();
}

