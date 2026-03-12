#include "Shader.h"

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>

std::string getTextFromFile(std::filesystem::path path)
{
    std::ifstream in(path, std::ios::in);
    const auto sz = std::filesystem::file_size(path);
    std::string result(sz, '\0');
    in.read(result.data(), sz);

    return result;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    load(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

unsigned int compileShader(unsigned int shaderType, const char* textShader, std::string shaderTypeName)
{
    unsigned shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &textShader, nullptr);   
    glCompileShader(shader);

    int  success;
    char infoLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "error: shader compilation of type: " << shaderTypeName << "\n" << infoLog << "\n---------------------------------------------------\n";
    }

    return shader;
}

void Shader::load(std::string vertexPath, std::string fragmentPath) 
{
    unsigned int vs = compileShader(GL_VERTEX_SHADER, getTextFromFile(vertexPath).c_str(), "VERTEX");
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, getTextFromFile(fragmentPath).c_str(), "FRAGMENT");
    textShader1 = getTextFromFile(vertexPath);
    textShader2 = getTextFromFile(fragmentPath);

    _id = glCreateProgram();
    glAttachShader(_id, vs);
    glAttachShader(_id, fs);
    glLinkProgram(_id);

    int  success;
    char infoLog[1024];

    glGetProgramiv(_id, GL_LINK_STATUS, &success);

    if(!success) 
    {
        glGetProgramInfoLog(_id, 1024, NULL, infoLog);
        std::cout << "error: program linking of type: " << "program" << "\n" << infoLog << "\n---------------------------------------------------\n";
        _id = -1;
        glDeleteProgram(_id);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() 
{
    glUseProgram(_id);
}

void Shader::setBool(const std::string& name, bool value) 
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string& name, int value) 
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
    std::cout << glGetError() << std::endl;
}

void Shader::setFloat(const std::string& name, float value) 
{
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
}

void Shader::setMat4(const std::string& name, glm::mat4 value) 
{
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) 
{
    glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) 
{
    glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
}

int Shader::GetId()
{
    return _id;
}

void Shader::log()
{
    std::cout << _id << std::endl;
    std::cout << textShader1 << std::endl;
    std::cout << textShader2 << std::endl;
}