#pragma once

#include <assimp/scene.h>

#include <vector>

#include <Renderer/Mesh.h>

class Mesh;

class ModelLoader {
public:
    static std::vector<Mesh*> LoadModel(std::string path);
    static void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes);
    static Mesh* parseMesh(aiMesh* mesh, aiMaterial* material);
};