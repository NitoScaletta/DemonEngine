#include <glad/glad.h>
#include <graphic/Shader.h>
#include <core/CoreFun.h>
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(){

}

Shader::Shader(VertexType type)
{
    initShader(type);
}

void Shader::initShader(VertexType type){
    if (type == VertexType::VERTEX)
        id = glCreateShader(GL_VERTEX_SHADER);
    if(type == VertexType::FRAGMENT)
        id = glCreateShader(GL_FRAGMENT_SHADER);
}

void Shader::checkLog(){
    int success;
    char infoLog[2048];
    glGetShaderiv(id,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(id, 2048, NULL, infoLog);
        std::cout<< pathtosource <<" ----> ERRORE COMOPILAZIONE SHADER" << std::endl << infoLog << std::endl;
    }

}

void Shader::compileShader()
{
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    checkLog();
}
void Shader::readSourceFile(const char*  path){
    pathtosource = path;
    char completePath[100] ="res/shaders/" ; 
    strncat(completePath, path, 99);
    std::ifstream file;
    file.open(completePath);
    if(file){
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string code = buffer.str();
        source = code.c_str();
        compileShader();
    }
    else{
        std::cout << path << "file non trovato" << std::endl;
    }
}


void Shader::deleteShader()
{
    glDeleteShader(id);
}

ShaderProgram::ShaderProgram()
{
    id = glCreateProgram();
    errors = 0;
}

ShaderProgram::ShaderProgram(unsigned int vid, unsigned int fid)
{
    id = glCreateProgram();
    compileShader(vid, fid);
}


void ShaderProgram::compileShader(unsigned int vid, unsigned int fid)
{
    glAttachShader(id, vid);
    glAttachShader(id, fid);
    glLinkProgram(id);
    checkLog();
}


void ShaderProgram::checkLog(){
    int success;
    glGetProgramiv(id,GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[2048];
        glGetShaderInfoLog(id, 2048, NULL, infoLog);
        std::cout<<" ERRORE COMOPILAZIONE PROGRAM SHADER"<< std::endl << infoLog << std::endl;
    }
}



void  ShaderProgram::use()
{
    glUseProgram(id);
}

void ShaderProgram::setUnifi(const char *name, int pos)
{
    use();
    int loc = getUniLocation(name);
    glUniform1i(loc, pos);
}

void ShaderProgram::setUniff(const char *name, float pos)
{
    use();
    int loc = getUniLocation(name);
    glUniform1f( loc, pos);
}



void ShaderProgram::setUniMat4f(const char* name,glm::mat4 matrix)
{
    use();
    int loc = getUniLocation(name);
    glUniformMatrix4fv(loc,1,GL_FALSE, &matrix[0][0]);
}


void ShaderProgram::setUniVector(const char *name, int size, const int *value)
{
    use();
    int loc = getUniLocation(name);
    glUniform1iv(loc, size, value);
}
void ShaderProgram::setUniVec3(const char *name, glm::vec3 vect)
{
    use();
    int loc = getUniLocation(name);
    glUniform3fv(loc, 1, &vect.x);
}


int ShaderProgram::getUniLocation(std::string name){
    if(uniformCache.find(name) != uniformCache.end())
        return uniformCache[name];

    int location = glGetUniformLocation(id, name.c_str());
    if (location == -1 && errors  < 2)
    {
        std::cout << "UNIFORM " << name << " NOT FOUND" << std::endl;
        errors++;
        return  -1;
    }

    uniformCache[name] = location;
    return location;
}
