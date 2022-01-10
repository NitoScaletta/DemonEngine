#include <Renderer/Shader.h>
#include <core/CoreFun.h>
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(){

}

Shader::Shader(int type)
{
    initShader(type);
}

void Shader::initShader(int type)
{
        id = glCreateShader(type);
}

void Shader::checkLog(){
    int success;
    char infoLog[2048];
    glGetShaderiv(id,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(id, 2048, NULL, infoLog);
        DE_CORE_ERROR("{0}----> ERRORE COMOPILAZIONE SHADER",pathtosource);  
        DE_CORE_TRACE("{0}",infoLog);
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
        DE_CORE_TRACE("{} has been loaded!", completePath);
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        std::string code = buffer.str();
        source = code.c_str();
        compileShader();
    }
    else{
        DE_CORE_WARNING("{0} file non trovato", path);
    }
}


void Shader::LoadDefault(const char* _source)
{
    glShaderSource(id, 1, &_source, NULL);
    glCompileShader(id);
    checkLog();
};


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
	char infoLog[2048];
    for (int i = 0; i< 2048; i++)
    {
        infoLog[i] = 'a';
    }
    glGetProgramiv(id,GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 2047, NULL, infoLog);
        DE_CORE_ERROR("ERRORE COMOPILAZIONE PROGRAM SHADER");
        DE_CORE_TRACE("{0}", infoLog);
    }
    else
        DE_CORE_TRACE("PROGRAM SHADER {} compiled succesfully", id);
}





void ShaderProgram::setUnifi(const char *name, int pos)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform1i(loc, pos);
}

void ShaderProgram::setUniIntVec(const char* name, int32_t* array, size_t count)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform1iv(loc, count, array);
}

void ShaderProgram::setUniff(const char *name, float pos)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform1f( loc, pos);
}



void ShaderProgram::setUniMat4f(const char* name,glm::mat4 matrix)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniformMatrix4fv(loc,1,GL_FALSE, &matrix[0][0]);
}


void ShaderProgram::setUniVector(const char *name, int size, const int *value)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform1iv(loc, size, value);
}


void ShaderProgram::setUniVec2(const char* name, glm::vec2 vect) 
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform2fv(loc, 1, &vect.x);
}

void ShaderProgram::setUniVec3(const char *name, glm::vec3 vect)
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform3fv(loc, 1, &vect.x);
}


void ShaderProgram::setUniVec4(const char* name, glm::vec4 vect) 
{
    glUseProgram(id);
    int loc = getUniLocation(name);
    glUniform4fv(loc, 1, &vect.x);
}



int ShaderProgram::getUniLocation(std::string name){
    if(uniformCache.find(name) != uniformCache.end())
        return uniformCache[name];

    int location = glGetUniformLocation(id, name.c_str());
    if (location == -1 && errors  < 2)
    {
        DE_CORE_WARNING("uniform {0} not found", name);
        errors++;
        return  -1;
    }

    uniformCache[name] = location;
    return location;
}
