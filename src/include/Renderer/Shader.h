#ifndef VERTEXSHADER_H_
#define VERTEXSHADER_H_
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <glad/glad.h>

#define VERTEX_SHADER 0x8B31
#define FRAGMENT_SHADER 0x8B30

class Shader{

    public:
        unsigned int id;
        const char *source;
        std::string pathtosource;

    private:
        void checkLog();

    public:
        Shader();
        Shader(int type);
        void compileShader();
        void deleteShader();
        void readSourceFile(const  char*  path);
        void LoadDefault(const char* source);
        void initShader(int type);
};

class ShaderProgram{
    public:
        unsigned int id;
        int errors;
        ShaderProgram();
        ShaderProgram(unsigned int vid, unsigned int fid);
        void compileShader(unsigned int vid, unsigned int fid);
        inline void use()       { glUseProgram(id); }
        inline void unbind()    { glUseProgram(0); }
        void setUnifi(const char* name, int pos);
        void setUniff(const char *name, float pos);
        void setUniMat4f(const char* name,glm::mat4 matrix);
        void setUniVector(const char* name, int size, const int* value);
        void setUniVec2(const char* name, glm::vec2 vect);
        void setUniVec3(const char* name, glm::vec3 vect);
        void setUniVec4(const char* name, glm::vec4 vect);
        void setUniIntVec(const char* name, int32_t* array, size_t count);

    private:
        std::unordered_map<std::string , int> uniformCache;
        void checkLog();
        int getUniLocation(std::string name);

};


static const char* basic_quad_vertex_shader = ""
"#version 450 core\n "
"layout(location = 0) in vec4 aPos;      \n"
"layout(location = 1) in vec4 aColor;    \n"
"layout(location = 2) in vec2 aTexCoord; \n"
"layout(location = 3) in float aTextID;  \n"
"layout(location = 4) in float aTilingF; \n"
"                                        \n"
"out vec2  FragPos;                      \n"
"out vec4  oColor;                       \n"
"out vec2  oTexCoord;                    \n"
"out float oTextID;                      \n"
"out float TilingFactor;                 \n"
"                                          "
"uniform mat4 aMVP;                      \n"
"                                        \n"
"void main()                             \n"
"{                                       \n"
"    TilingFactor = aTilingF;            \n"  
"    oColor = aColor;                    \n"
"    oTexCoord = aTexCoord;              \n"
"    oTextID = aTextID;                  \n"
"                                        \n"
"    gl_Position = aMVP * aPos;          \n"
"    FragPos = aPos.xy;                  \n"
"}";

static const char* basic_circle_vertex_shader = "\n"
"#version 450 core                              \n"
"layout(location = 0) in vec4 aPos;             \n"
"layout(location = 1) in vec3 aLocalPosition;   \n"
"layout(location = 2) in vec4 aColor;           \n"
"layout(location = 3) in float aThickness;      \n"
"layout(location = 4) in float aFade;           \n"
"                                               \n"
"                                               \n"
"out vec2  FragPos;                             \n"
"out vec4  oColor;                              \n"
"out float  oThickness;                         \n"
"out float oFade;                               \n"
"                                               \n"
"uniform mat4 aMVP;                             \n"
"                                               \n"
"void main()                                    \n"
"{                                              \n"
"    oColor = aColor;                           \n"
"    oThickness = aThickness;                   \n"
"    oFade = aFade;                             \n"
"                                               \n"
"    gl_Position =  aMVP * aPos;                \n"
"    FragPos = aLocalPosition.xy;               \n"
"}                                              \n";

static const char* basic_quad_fragment_shader = "       \n"
"#version 450 core                                      \n"
"out vec4 FragColor;                                    \n"
"                                                       \n"
"in vec2 oTexCoord;                                     \n"
"in vec4 oColor;                                        \n"
"in vec4 FragPos;                                       \n"
"in float oTextID;                                      \n"
"in float TilingFactor;                                 \n"
"uniform sampler2D textures[32];                        \n"
"                                                       \n"
"void main()                                            \n"
"{                                                      \n"
"  FragColor = texture(textures[int(oTextID)], oTexCoord * TilingFactor) * oColor;   \n"
"}                                                      \n";

static const char* basic_circle_fragment_shader = "                     \n"
"#version 450 core                                                      \n"
"out vec4 FragColor;                                                    \n"
"in vec2 TexCoord;                                                      \n"
"in vec2 FragPos;                                                       \n"
"in vec4 oColor;                                                        \n"
"in float oFade;                                                        \n"
"                                                                       \n"
"void main(){                                                           \n"
"                                                                       \n"
"    float thickness = 1;                                               \n"
"    float fade =  oFade;                                               \n"
"    float distance =  1 - length(FragPos.xy);                          \n"
"    float circleAlpha = smoothstep(0.0, fade, distance);               \n"
"    circleAlpha *= smoothstep(thickness + fade, thickness, distance);  \n"
""
""
"    FragColor = oColor;                                                \n"
"    FragColor.a = circleAlpha;                                         \n"
"}\n";

#endif // VERTEXSHADER_H_
