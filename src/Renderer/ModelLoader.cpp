#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#include <string>
#include <iostream>

std::vector<Mesh*> ModelLoader::LoadModel(std::string path)
{
    std::vector<Mesh*> meshes;

    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_MakeLeftHanded | 
        aiProcess_GenNormals |     
        aiProcess_OptimizeMeshes |
        aiProcess_CalcTangentSpace
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return meshes;
    }

    processNode(scene->mRootNode, scene, meshes);
    return meshes;
}

void ModelLoader::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes) 
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) 
    {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
        aiMaterial* aiMateral = scene->mMaterials[aiMesh->mMaterialIndex];
        meshes.push_back(parseMesh(aiMesh, aiMateral));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) 
    {
        processNode(node->mChildren[i], scene, meshes);
    }
}

Mesh* ModelLoader::parseMesh(aiMesh* aimesh, aiMaterial* material) 
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    vertices.reserve(aimesh->mNumVertices);
    indices.reserve(aimesh->mNumFaces * 3);

    for (unsigned int i = 0; i < aimesh->mNumVertices; i++) 
    {
        Vertex v;
        v.Position = { aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z };
        v.Normal = { aimesh->mNormals[i].x,  aimesh->mNormals[i].y,  aimesh->mNormals[i].z };
        if (aimesh->mTextureCoords[0])
            v.TexCoords = { aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y };
        else
            v.TexCoords = { 0.0f, 0.0f };
        vertices.push_back(v);
    }

    for (unsigned int i = 0; i < aimesh->mNumFaces; i++) 
    {
        aiFace face = aimesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    Mesh* mesh = new Mesh();
    mesh->setup(vertices.data(), vertices.size(), indices.data(), indices.size());
    return mesh;
}