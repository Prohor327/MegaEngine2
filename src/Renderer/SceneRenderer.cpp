#include "SceneRenderer.h"

#include <glad/glad.h>
#include <iostream>
#include <Renderer/MeshRenderer.h>
#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Core.h>
#include <Tools/Vector.h>

void SceneRenderer::Setup(float vertices[], int indices[], int sizeVertices, int sizeIndices, std::vector<MeshRenderer*> &meshRenderers, std::vector<std::string> texturesName, Camera* currentCamera)
{
    YAML::Node shaderConf = YAML::LoadFile("res/Configs/Shaders.yaml");
    _amountShaders = shaderConf.size();
    _meshRenderers = meshRenderers;
    _currentCamera = currentCamera;
    int amountMeshs = _meshRenderers.size();

    for(int i = 0; i < _amountShaders; i++)
    {
        std::pair<std::string, Shader*> pair = std::make_pair(shaderConf[i]["name"].as<std::string>(),
         new Shader(shaderConf[i]["vertex"].as<std::string>(), shaderConf[i]["fragment"].as<std::string>()));
        _shaders.insert(pair);
    }

    for(int i = 0; i < amountMeshs; i++)
    {
        _meshRenderers[i]->shader = _shaders[_meshRenderers[i]->shaderName];
    }

    glGenVertexArrays(1, &_vertexDataVAO);
    glGenBuffers(1, &_vertexDataVBO);
    glGenBuffers(1, &_vertexDataEBO);

    glBindVertexArray(_vertexDataVAO);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexDataVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexDataEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    for (std::string textureName : texturesName)
    {
        YAML::Node textureConf = YAML::LoadFile("res/Configs/Textures/" + textureName + ".yaml");
        std::cout << "res/Textures/" + textureConf["name"].as<std::string>() << std::endl;
        _textures.emplace_back(0, 0, " ", "res/Textures/" + textureConf["name"].as<std::string>());
    }
}

void SceneRenderer::Render()
{
    glBindVertexArray(_vertexDataVAO);
    int amountMeshs = _meshRenderers.size();
 


    for (int i = 0; i < amountMeshs; i++)
    {
        _textures[i].ActiveTexture();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = _currentCamera->GetProjection();
        view = _currentCamera->GetView();
        //view = glm::translate(view, _meshRenderers[i]->transform->position);
        //view = glm::rotate(view, glm::radians(_meshRenderers[i]->transform->rotation.x), vector::right);
        //view = glm::rotate(view, glm::radians(_meshRenderers[i]->transform->rotation.y), vector::up);
        //view = glm::rotate(view, glm::radians(_meshRenderers[i]->transform->rotation.z), vector::forward);
        view = glm::scale(view, _meshRenderers[i]->transform->scale);
        _meshRenderers[i]->shader->setMat4("projection", projection);
        _meshRenderers[i]->shader->setMat4("view", view);
        _meshRenderers[i]->shader->setMat4("model", _meshRenderers[i]->transform->GetModel());
        _meshRenderers[i]->shader->use();
        glDrawElementsBaseVertex(GL_TRIANGLES, _meshRenderers[i]->amountIndices, GL_UNSIGNED_INT, 0, _meshRenderers[i]->baseIndex);
    }
}

void SceneRenderer::cleanUp()
{
    _meshRenderers.clear();
    _shaders.clear();
    glDeleteVertexArrays(1, &_vertexDataVAO);
    glDeleteBuffers(1, &_vertexDataVBO);
    glDeleteBuffers(1, &_vertexDataEBO);
}