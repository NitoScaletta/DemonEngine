#include "Renderer/renderer.h"
#include "Renderer/glObjects.h"
#include "Renderer/Shader.h"
#include <core/Window.h>
#include <iostream>
#include <core/Log.h>

QuadBufferData *Renderer::s_QuadBufferData;
CircleBufferData *Renderer::s_CircleBufferData;
RendererStats Renderer::Stats;

glm::mat4 *Renderer::s_ProjViewMatrix;


glm::vec4 QuadVerticesBase[4];
glm::vec2 TextureCoordsBase[4];

Renderer::Renderer()
{
}

Renderer::~Renderer() 
{
}

void Renderer::End() 
{
    glfwSwapBuffers(CrossPlatformWindow::GetNativeWindow());
    glfwPollEvents();

    s_QuadBufferData->QuadVerticesIndex = 0;
    s_QuadBufferData->IndicesIndex = 0;
    s_CircleBufferData->CircleVerticesIndex = 0;
    s_CircleBufferData->IndicesIndex = 0;
    Stats.CircleIndex = 0;
    Stats.QuadIndex = 0;
    Stats.DrawCalls = 0;
}

void Renderer::ImGuiInit() 
{
    const char* glsl_version = "#version 430";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(CrossPlatformWindow::GetNativeWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Renderer::ImGuiStart()
{
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
}

void Renderer::ImGuiEnd() 
{
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::ImGuiClose() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void Renderer::Clear(float r, float g, float b, float alpha)
{
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  QUADS RENDERING //////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////TEXTURED/////////////////////////////////////////////////////////////////////


void Renderer::DrawTexturedQuad(const glm::vec3& Position, Texture& texture, const float Scale, const float Rotation, const float TilingFactor, const glm::vec4& Color)
{
    bool found = false;
    if (s_QuadBufferData->TextureSlotIndex >= MaxTextureSlots)
    {
        RenderAll();
        s_QuadBufferData->QuadVerticesIndex = 0;
        s_QuadBufferData->IndicesIndex = 0;
        s_QuadBufferData->TextureSlotIndex = 1;
    }
    if (s_QuadBufferData->TextureSlotIndex > 0)
    {
        for (size_t i = 0; i < s_QuadBufferData->TextureSlotIndex; i++)
        {
            if (s_QuadBufferData->Textures[i].GetTextureSlot() == texture.GetTextureSlot())
                found = true;
        }
    }
    if (!found);
		LoadTexture(texture);

	DrawQuad(Position, Rotation, glm::vec3(Scale, Scale, 1), Color, texture.GetTextureSlot(), TilingFactor);
}

void Renderer::DrawQuad(QuadData& quad)
{
    glm::mat4 transform =   glm::translate(glm::mat4(1.0f), quad.position) *
                            glm::rotate(glm::mat4(1.0f),glm::radians(quad.rotation),glm::vec3(0.0f,0.0f,1.0f)) *
                            glm::scale(glm::mat4(1.0f), quad.size);
    DrawQuad(transform, quad.color, quad.TextureSlotIndex);
}

void Renderer::DrawQuad(const glm::vec3& Position, const float& Rotation, const glm::vec3& Scale, const glm::vec4& Color, const float TextureID, const float TilingFactor)
{
    glm::mat4 transform =   glm::translate(glm::mat4(1.0f), Position) *
                            glm::rotate(glm::mat4(1.0f),glm::radians(Rotation),glm::vec3(0.0f,0.0f,1.0f)) *
                            glm::scale(glm::mat4(1.0f), Scale);
    DrawQuad(transform, Color, TilingFactor, TextureID);
}

void Renderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color, const float TilingFactor, const float TextureID)
{
    if (s_QuadBufferData->QuadVerticesIndex + 4 >= MaxQuadVertices)
    {
        RenderAll();
        s_QuadBufferData->QuadVerticesIndex = 0;
        s_QuadBufferData->IndicesIndex = 0;
    }
    for (size_t i = 0; i < 4; i++)
    {
        s_QuadBufferData->QuadVertices[s_QuadBufferData->QuadVerticesIndex].Position = transform * QuadVerticesBase[i];
        s_QuadBufferData->QuadVertices[s_QuadBufferData->QuadVerticesIndex].Color = color;
        s_QuadBufferData->QuadVertices[s_QuadBufferData->QuadVerticesIndex].TextureCoordinates = TextureCoordsBase[i];
        s_QuadBufferData->QuadVertices[s_QuadBufferData->QuadVerticesIndex].TextureID = TextureID;
        s_QuadBufferData->QuadVertices[s_QuadBufferData->QuadVerticesIndex].TilingFactor = TilingFactor;
        s_QuadBufferData->QuadVerticesIndex++;
    }
    s_QuadBufferData->IndicesIndex += 6;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////  CIRCLE RENDERERING ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
//TODO: Find antoher solution for the depth problem

void Renderer::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float fade, float thickness)
{
    if (s_CircleBufferData->CircleVerticesIndex + 4 >= MaxQuadVertices)
    {
        RenderAll();
        s_CircleBufferData->CircleVerticesIndex = 0;
        s_CircleBufferData->IndicesIndex = 0;
    }
    float zDepth = static_cast<float>(s_CircleBufferData->CircleVerticesIndex) / 100000.0f;
    for (size_t i = 0; i < 4; i++)
    {
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].Position = transform * QuadVerticesBase[i];
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].Position.z += zDepth;
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].LocalPosition = 2.0f * QuadVerticesBase[i];
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].Color = color;
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].Fade = fade;
        s_CircleBufferData->CircleVertices[s_CircleBufferData->CircleVerticesIndex].Thickness = thickness;
        s_CircleBufferData->CircleVerticesIndex++;
    }
    s_CircleBufferData->IndicesIndex += 6;

}


void Renderer::DrawCircle(const QuadData& quad)
{
    glm::mat4 transform =   glm::translate(glm::mat4(1.0f), quad.position) *
                            glm::scale(glm::mat4(1.0f), glm::vec3(quad.size));
    DrawCircle(transform, quad.color);
}


void Renderer::DrawCircle(const glm::vec3& Position, const glm::vec4& Color, glm::vec3 Scale, float fade, float thickness)
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
                          glm::scale(glm::mat4(1.0f), Scale);
    DrawCircle(transform, Color, fade, thickness);
}



////////////////////////////////////////////////////////////////////////////////////////
/////  INITIALIZATION /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

void Renderer::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        DE_CORE_ERROR("Failed to initialize GLAD");
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    s_QuadBufferData = new QuadBufferData;
    s_CircleBufferData = new CircleBufferData;
	CreateIndices();
    InitiateQuadsBatch();
    uint32_t data = 0xffffffff;
    s_QuadBufferData->Textures[0] = Texture(1, 1, &data);
	s_QuadBufferData->Textures[0].bindSlot(s_QuadBufferData->TextureSlotIndex);
}



void Renderer::InitiateQuadsBatch()
{
    s_QuadBufferData->QuadsVbo = new VertexBuffer;
    s_QuadBufferData->QuadsVao = new VertexArray;
    s_QuadBufferData->QuadsEbo = new ElementBuffer;
    s_QuadBufferData->QuadsPs  = new ShaderProgram;
    s_QuadBufferData->QuadsVao->bind();
    s_QuadBufferData->QuadsEbo->bind();
    s_QuadBufferData->QuadsVbo->bindDynamic<QuadVertex>(MaxQuadVertices+10);
    s_QuadBufferData->QuadsVao->QuadLayout();
    s_QuadBufferData->QuadsEbo->set(s_QuadBufferData->Indices, MaxQuadIndices);
    Shader fs, vs;
    vs.initShader(VERTEX_SHADER);
    fs.initShader(FRAGMENT_SHADER);
    vs.LoadDefault(basic_quad_vertex_shader);
    fs.LoadDefault(basic_quad_fragment_shader);
    s_QuadBufferData->QuadsPs->compileShader(vs.id, fs.id);
    int32_t TextureSampler[MaxTextureSlots];
    for (size_t i = 0; i < MaxTextureSlots; i++)
    {
        TextureSampler[i] = i;
    }
    s_QuadBufferData->QuadsPs->setUniIntVec("textures", TextureSampler, 32);
    
    s_QuadBufferData->QuadsVbo->unbind();
    s_QuadBufferData->QuadsVao->unbind();
    s_QuadBufferData->QuadsEbo->unbind();
    s_QuadBufferData->QuadsPs->unbind();

    s_CircleBufferData->CirclesVbo = new VertexBuffer;
    s_CircleBufferData->CirclesVao = new VertexArray;
    s_CircleBufferData->CirclesEbo = new ElementBuffer;
    s_CircleBufferData->CirclesPs  = new ShaderProgram;
    s_CircleBufferData->CirclesVao->bind();
    s_CircleBufferData->CirclesEbo->bind();
    s_CircleBufferData->CirclesVbo->bindDynamic<CircleVertex>(MaxQuadVertices+10);
    s_CircleBufferData->CirclesVao->CircleLayout();
    s_CircleBufferData->CirclesEbo->set(s_QuadBufferData->Indices, MaxQuadIndices);
    vs.initShader(VERTEX_SHADER);
    fs.initShader(FRAGMENT_SHADER);
    vs.LoadDefault(basic_circle_vertex_shader);
    fs.LoadDefault(basic_circle_fragment_shader);
    s_CircleBufferData->CirclesPs->compileShader(vs.id, fs.id); 
  

    s_CircleBufferData->CirclesVbo->unbind();
    s_CircleBufferData->CirclesVao->unbind();
    s_CircleBufferData->CirclesEbo->unbind();
    s_CircleBufferData->CirclesPs->unbind();


    QuadVerticesBase[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    QuadVerticesBase[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    QuadVerticesBase[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    QuadVerticesBase[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    TextureCoordsBase[0] = { 0, 0 };
    TextureCoordsBase[1] = { 1, 0 };
    TextureCoordsBase[2] = { 1, 1 };
    TextureCoordsBase[3] = { 0, 1 };
    }


void Renderer::CreateIndices()
{
    int32_t offset = 0;
    for (int i = 0; i < MaxQuadIndices; i += 6) {
        s_QuadBufferData->Indices[i]   = 0 + offset;
        s_QuadBufferData->Indices[i+1] = 1 + offset;
        s_QuadBufferData->Indices[i+2] = 2 + offset;
        s_QuadBufferData->Indices[i+3] = 2 + offset;
        s_QuadBufferData->Indices[i+4] = 3 + offset;
        s_QuadBufferData->Indices[i+5] = 0 + offset;
        offset += 4;
    }
       
}




/////////////////////////////////////////////////////////////////////////////////
//////////////// RENDERING /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void Renderer::RenderAll()
{
    if (s_QuadBufferData->QuadVerticesIndex > 0)
    {
        for (size_t i = 0; i < s_QuadBufferData->TextureSlotIndex; i++)
            s_QuadBufferData->Textures[i].bindSlot(i);

    	s_QuadBufferData->QuadsVao->bind();
    	s_QuadBufferData->QuadsPs->setUniMat4f("aMVP", *s_ProjViewMatrix);
        s_QuadBufferData->QuadsVbo->bind();
    	s_QuadBufferData->QuadsVbo->loadDynamic<QuadVertex>(0, s_QuadBufferData->QuadVerticesIndex, s_QuadBufferData->QuadVertices);
        Stats.QuadIndex += s_QuadBufferData->QuadVerticesIndex;
		glDrawElements(GL_TRIANGLES, s_QuadBufferData->IndicesIndex, GL_UNSIGNED_INT, nullptr );
        Stats.DrawCalls++;
    }
    if (s_CircleBufferData->CircleVerticesIndex > 0)
    {
    	s_CircleBufferData->CirclesVao->bind();
    	s_CircleBufferData->CirclesPs->setUniMat4f("aMVP", *s_ProjViewMatrix);
        s_CircleBufferData->CirclesVbo->bind();
    	s_CircleBufferData->CirclesVbo->loadDynamic<CircleVertex>(0, s_CircleBufferData->CircleVerticesIndex, s_CircleBufferData->CircleVertices);
        Stats.CircleIndex += s_CircleBufferData->CircleVerticesIndex;
		glDrawElements(GL_TRIANGLES, s_CircleBufferData->IndicesIndex, GL_UNSIGNED_INT, nullptr );
        Stats.DrawCalls++;
    }
}






//////////////////////////////////////////////////////////////////////////////////////
//////////////////// TEXTURES ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


void Renderer::LoadTexture(const char* path)
{
    if (s_QuadBufferData->TextureSlotIndex < MaxTextureSlots)
    {
        s_QuadBufferData->Textures[s_QuadBufferData->TextureSlotIndex] = Texture(path);
        s_QuadBufferData->Textures[s_QuadBufferData->TextureSlotIndex].bindSlot(s_QuadBufferData->TextureSlotIndex);
        s_QuadBufferData->TextureSlotIndex++;
    }
    else
        DE_CORE_ERROR(" Too many texture loaded ");

}


void Renderer::LoadTexture(Texture& texture)
{
    if (s_QuadBufferData->TextureSlotIndex < MaxTextureSlots)
    {
        s_QuadBufferData->Textures[s_QuadBufferData->TextureSlotIndex] = texture;
		texture.bindSlot(s_QuadBufferData->TextureSlotIndex);
        s_QuadBufferData->TextureSlotIndex++;
    }
    else
        DE_CORE_ERROR(" Too many texture loaded ");

}
