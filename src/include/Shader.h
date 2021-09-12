#ifndef VERTEXSHADER_H_
#define VERTEXSHADER_H_
#include "glm/glm.hpp"
#include <unordered_map>
#include <string>

enum VertexType{VERTEX, FRAGMENT};

class Shader{

    public:
        unsigned int id;
        const char *source;
        std::string pathtosource;

    private:
        void checkLog();

    public:
        Shader();
        Shader(VertexType type);
        void compileShader();
        void deleteShader();
        void readSourceFile(const  char*  path);
        void initShader(VertexType type);
};

class ShaderProgram{
    public:
        unsigned int id;
        int errors;
        ShaderProgram();
        ShaderProgram(unsigned int vid, unsigned int fid);
        void compileShader(unsigned int vid, unsigned int fid);
        void use();
        void setUnifi(const char* name, int pos);
        void setUniff(const char *name, float pos);
        void setUniMat4f(const char* name,glm::mat4 matrix);
        void setUniVector(const char* name, int size, const int* value);
        void setUniVec3(const char* name, glm::vec3 vect);

    private:
        std::unordered_map<const char*, int> uniformCache;

        void checkLog();
        int getUniLocation(const char* name);

};


#endif // VERTEXSHADER_H_
