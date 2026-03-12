#pragma once

#include <glad/glad.h>
#include <Renderer/MeshRenderer.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <Renderer/Texture.h>
#include <Game/Camera.h>

#include "Shader.h"

class SceneRenderer
{
public:
    void Setup(float vertices[], int indices[], int sizeVertices, int sizeIndices,
    std::vector<MeshRenderer*> &meshRenderers, std::vector<std::string> texturesName, Camera* currentCamera);
    void Render();
    void cleanUp();
    //void addShader();

private:
    unsigned int _vertexDataVAO = 0, _vertexDataVBO = 0, _vertexDataEBO = 0, _amountShaders = 0;
    int _amountVertices = 0;
    Camera* _currentCamera;
    std::unordered_map<std::string, Shader*> _shaders;
    std::vector<MeshRenderer*> _meshRenderers;
    std::vector<Texture> _textures;
};