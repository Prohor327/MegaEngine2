#pragma once 

#include <Renderer/Shader.h>
#include <ComponentSystem/Component.h>
#include <Renderer/Mesh.h>
#include <Renderer/Texture.h>

#include <memory>


class MeshRenderer : public ComponentSystem::Component
{
public: 
    MeshRenderer() = default;

    std::shared_ptr<Model> model = nullptr;
    std::shared_ptr<Shader> shader = nullptr;
    std::shared_ptr<Texture> texture = nullptr;
    void Draw();
};  