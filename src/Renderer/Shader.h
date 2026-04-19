#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader 
{
public:
    Shader(std::string name, std::string vertexPath, std::string fragmentPath);
    ~Shader();
    void load(std::string vertexPath, std::string fragmentPath);
    void use();
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);
    void setMat4(const std::string& name, glm::mat4 value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec2(const std::string& name, const glm::vec2& value);
    int GetId();
    std::string GetName();
    void log();
private:
    int _id = 0;
    std::string _name;
};