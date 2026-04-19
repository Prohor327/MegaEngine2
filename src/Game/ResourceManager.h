#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <yaml-cpp/yaml.h>

#include <Renderer/Texture.h>
#include <Renderer/Mesh.h>
#include <Renderer/Shader.h>

class ResourceManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> _textures;
    std::unordered_map<std::string, std::shared_ptr<Model>> _models;
    std::unordered_map<std::string, std::shared_ptr<Shader>> _shaders;

    ResourceManager() = default;
    ~ResourceManager() = default;

public: 
    static ResourceManager& GetInstance();

    ResourceManager(const ResourceManager&) = delete;
    void operator=(const ResourceManager&) = delete;

    std::shared_ptr<Texture> GetTexture(const std::string& path);
    std::shared_ptr<Model> GetModel(const std::string& path);
    std::shared_ptr<Shader> GetShader(const std::string& name, const std::string& vPath, const std::string& fPath);
};