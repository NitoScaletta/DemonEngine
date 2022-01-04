#ifndef RENDERER_H_
#define RENDERER_H_

#include <core/core.h>
#include <Renderer/ParticleSystem.h>
#include <Renderer/Camera2d.h>
#include "core/Math.h"
#include "core/Log.h"


static constexpr size_t MaxQuads = 10000;
static constexpr size_t MaxQuadVertices = MaxQuads * 4;
static constexpr size_t MaxQuadIndices = static_cast<size_t>(MaxQuadVertices * 1.5f);
static constexpr size_t MaxTextureSlots = 32;


struct RendererStats
{
    uint32_t DrawCalls = 0;
    size_t  QuadIndex = 0;
    size_t  CircleIndex = 0;
};

struct QuadBufferData
{
         std::unique_ptr<VertexArray>      QuadsVao;
         std::unique_ptr<VertexBuffer>     QuadsVbo;
         std::unique_ptr<ElementBuffer>    QuadsEbo;
         std::unique_ptr<ShaderProgram>    QuadsPs;
         QuadVertex       QuadVertices[MaxQuadVertices];
         size_t           QuadVerticesIndex = 0;
         uint32_t         Indices[MaxQuadIndices];
         size_t           IndicesIndex = 0;
         std::shared_ptr<Texture> Textures[MaxTextureSlots];
         size_t           TextureSlotIndex = 1;
};


struct CircleBufferData
{
         std::unique_ptr<VertexArray>      CirclesVao;
         std::unique_ptr<VertexBuffer>     CirclesVbo;
         std::unique_ptr<ElementBuffer>    CirclesEbo;
         std::unique_ptr<ShaderProgram>    CirclesPs;
         CircleVertex     CircleVertices[MaxQuadVertices];
         size_t           CircleVerticesIndex = 0;
         //uint32_t         Indices[MaxQuadIndices];
         size_t           IndicesIndex = 0;
};


class Renderer
{
    public:
        ~Renderer();

        static void init();
        static void Clear(float r = 1.0f, float g = 1.0f, float b = 1.0f, float alpha = 1.0f);
        static void End();

        static void ImGuiInit();
        static void ImGuiStart();
        static void ImGuiEnd();    
        static void ImGuiClose();    

        static void SetViewProjMatrix(std::shared_ptr<glm::mat4> m) { s_ProjViewMatrix = m; };

        static void DrawQuad(QuadData& quad);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = { 1, 1, 1, 1 }, const float TilingFactor = 1.0f, const float TextureID = 0);
        static void DrawQuad(const glm::vec3& Position, const float& Rotation = 0, const glm::vec3& Scale = { 1.0f, 1.0f, 1.0f }, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f }, const float TextureID = 0, const float TilingFactor = 1);

        static void DrawTexturedQuad(const glm::vec3& Position, std::shared_ptr<Texture> Texture,  const float Scale = 1.0f, const float Rotation = 0.0f, const float TilingFactor = 1, const glm::vec4& Color = { 1.0f, 1.0f, 1.0f, 1.0f});
        static void DrawTexturedQuad(const glm::mat4& transform, std::shared_ptr<Texture> Texture, const float TilingFactor = 1, const glm::vec4& Color = { 1.0f, 1.0f, 1.0f, 1.0f});
        static void DrawSprite(const glm::vec3& Position, std::shared_ptr<SubTexture> SubTexture,  const float Scale = 1.0f, const float Rotation = 0.0f, const glm::vec4& Color = { 1.0f, 1.0f, 1.0f, 1.0f });
        //static void DrawParticle(ParticleSystem* Particles);

        static void DrawCircle(const glm::vec3& Position, const glm::vec4 & Color = { 1, 1, 1, 1 }, const glm::vec3 Scale = { 1.0f, 1.0f, 1.0f},  float fade = 0.005, float thickness = 1);
        static void DrawCircle(const glm::mat4& transform, const glm::vec4& color = { 1, 1, 1, 1 }, float fade = 0.005, float thickness = 1);
        static void DrawCircle(const QuadData& quad);

        static void RenderAll();
        static const RendererStats& GetStats() { return Stats; }

    private:

        Renderer();
        static void InitiateQuadsBatch();
        static void CreateIndices();
        static void LoadTexture(std::shared_ptr<Texture> texture);
        static void CheckTexture(std::shared_ptr<Texture> texture);

        static std::shared_ptr<QuadBufferData> s_QuadBufferData;
        static std::shared_ptr<CircleBufferData> s_CircleBufferData;
        static RendererStats Stats;
        static std::shared_ptr<glm::mat4> s_ProjViewMatrix;
};



#endif // RENDERER_H_
