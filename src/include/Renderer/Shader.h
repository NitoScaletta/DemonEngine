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
        void initShader(int type);
};

class ShaderProgram{
    public:
        unsigned int id;
        int errors;
        ShaderProgram();
        ShaderProgram(unsigned int vid, unsigned int fid);
        void compileShader(unsigned int vid, unsigned int fid);
        inline void use() { glUseProgram(id); }
        void setUnifi(const char* name, int pos);
        void setUniff(const char *name, float pos);
        void setUniMat4f(const char* name,glm::mat4 matrix);
        void setUniVector(const char* name, int size, const int* value);
        void setUniVec3(const char* name, glm::vec3 vect);

    private:
        std::unordered_map<std::string , int> uniformCache;
        void checkLog();
        int getUniLocation(std::string name);

};


#endif // VERTEXSHADER_H_
