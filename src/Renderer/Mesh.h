#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Renderer/Texture.h>
#include <Renderer/ModelLoader.h>

class ModelLoader;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    unsigned int Vao = 0, indexCount = 0;

    Mesh() = default;
    void setup(const Vertex* vertices, size_t vCount, const unsigned int* indices, size_t iCount);

private:
    unsigned int _vbo = 0, _ebo = 0;
};

class Model {
public:
    std::vector<Mesh*> meshes;

    Model(const std::string& path);
};