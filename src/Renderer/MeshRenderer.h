#pragma once 

#include <Renderer/Shader.h>
#include <Game/Transform.h>
#include <ComponentSystem/Component.h>

#include <string>

class MeshRenderer : public ComponentSystem::Component
{
public: 
    int baseIndex = 0;
    float amountIndices = 0;
    Shader *shader = nullptr;
    std::string shaderName = "0";
    
    MeshRenderer(GameObject* gameObject, int baseIndex, int amountIndices, std::string shaderName);
    MeshRenderer(int baseIndex, int amountIndices, std::string shaderName);
    MeshRenderer(GameObject* gameObject);
};  