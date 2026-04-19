#include "ResourceManager.h"

ResourceManager& ResourceManager::GetInstance()
{
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& path) {
    if (_textures.count(path))
    {
        return _textures[path];
    }

    std::shared_ptr<Texture> tex = std::make_shared<Texture>(" ", path);
    return _textures[path] = tex;
}

std::shared_ptr<Model> ResourceManager::GetModel(const std::string& path) {
    if (_models.count(path))
    {
        return _models[path];
    }

    std::shared_ptr<Model> model = std::make_shared<Model>(path);
    return _models[path] = model;
}

std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name, const std::string& vPath, const std::string& fPath) {
    if (_shaders.count(name))
    {
        return _shaders[name];
    }

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(name, vPath, fPath);
    return _shaders[name] = shader;
}