#ifndef RENDERER_H_
#define RENDERER_H_
#include <core/core.h>
#include <Renderer/Camera2d.h>

#define MAX_QUAD 10000
#define MAX_QUAD_VERTICES MAX_QUAD*4
#define MAX_QUAD_INDICES static_cast<size_t>(MAX_QUAD_VERTICES * 1.5f)


struct RendererStats
{
    uint32_t DrawCalls = 0;
    size_t  QuadIndex = 0;
    size_t  CircleIndex = 0;
};

struct QuadBufferData
{
         VertexArray      *QuadsVao;
         VertexBuffer     *QuadsVbo;
         ElementBuffer    *QuadsEbo;
         ShaderProgram    *QuadsPs;
         QuadVertex       QuadVertices[MAX_QUAD_VERTICES + 4];
         size_t           QuadVerticesIndex = 0;
         uint32_t         Indices[MAX_QUAD_INDICES];
         size_t           IndicesIndex = 0;

};


struct CircleBufferData
{
         VertexArray      *CirclesVao;
         VertexBuffer     *CirclesVbo;
         ElementBuffer    *CirclesEbo;
         ShaderProgram    *CirclesPs;
         CircleVertex     CircleVertices[MAX_QUAD_VERTICES+4];
         size_t           CircleVerticesIndex = 0;
         uint32_t         Indices[MAX_QUAD_INDICES];
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

        static void SetViewProjMatrix(glm::mat4 *m) { s_ProjViewMatrix = m; };

        static void DrawQuad(QuadData& quad);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color = { 0, 0, 0, 1 } );
        static void DrawQuad(const glm::vec3& Position, const float& Rotation = 0, const glm::vec3& Scale = { 1.0f, 1.0f, 1.0f }, const glm::vec4& Color = { 1.0f,1.0f,1.0f,1.0f });


        static void DrawCircle(const glm::mat4& transform, const glm::vec4& color = { 0, 0, 0, 1 });
        static void DrawCircle(const QuadData& quad);

        static void RenderAll();
        static const RendererStats& GetStats()  { return Stats; }

    private:
        Renderer();
        static void InitiateQuadsBatch();
        static void CreateIndices();

        static glm::vec4 QuadVerticesBase[4];
        static QuadBufferData *s_QuadBufferData;
        static CircleBufferData *s_CircleBufferData;
        static RendererStats Stats;
        static glm::mat4 *s_ProjViewMatrix;
};



#endif // RENDERER_H_
