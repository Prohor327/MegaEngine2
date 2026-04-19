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
    void setup(std::vector<MeshRenderer*> *meshRenderers);
    void Render();
    void cleanUp();

private:
    std::vector<MeshRenderer*> *_meshRenderers;
};