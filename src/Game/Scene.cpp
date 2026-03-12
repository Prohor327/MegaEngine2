#include "Scene.h"

#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <glm/vec3.hpp>
#include <memory>


Scene::Scene(std::string sceneName)
{
    Load(sceneName);
}

void Scene::Load(std::string sceneName)
{
    YAML::Node sceneConf = YAML::LoadFile("res/Scenes/" + sceneName + ".yaml");

    int amountVertices = 0, amountIndices = 0, idxVertices = 0, idxIndices = 0, amountObjects = sceneConf["Objects"].size();
    std::vector<MeshRenderer*> meshRenderers;

    //load objects

    std::vector<YAML::Node> meshRendereresConfigs;

    _gameObjects.clear();

    for (int i = 0; i < amountObjects; i++)
    {
        YAML::Node node = sceneConf["Objects"]["obj" + std::to_string(i)];

        Transform transform;
        for (int j = 0; j < 3; ++j)
        {
            transform.position[j] = node["transforms"][j].as<float>();
            transform.rotation[j] = node["transforms"][j + 3].as<float>();
            transform.scale[j] = node["transforms"][j + 6].as<float>();

            std::cout << "pos" << node["transforms"][j].as<float>() << "rot" <<
                node["transforms"][j + 3].as<float>() << "scale" <<
                node["transforms"][j + 6].as<float>() << std::endl;
        }

        _gameObjects.emplace_back(std::make_unique<GameObject>(transform));

        if (node["Components"]["MeshRenderer"])
        {
            meshRendereresConfigs.push_back(node["Components"]["MeshRenderer"]);
            amountVertices += node["Components"]["MeshRenderer"]["vertices"].size();
            amountIndices += node["Components"]["MeshRenderer"]["indices"].size();
            MeshRenderer* meshRenderer = &_gameObjects[i]->AddComponent<MeshRenderer>(_gameObjects[i].get());
            meshRenderers.push_back(meshRenderer);
        }

        if (node["Components"]["Camera"])
        {
            YAML::Node cameraNode = node["Components"]["Camera"];
            Camera& camRef = _gameObjects[i]->AddComponent<Camera>(_gameObjects[i].get(),
                cameraNode["fov"].as<float>(), cameraNode["far"].as<float>(), cameraNode["near"].as<float>());
            AddCamera(&camRef);
        }

    }

    SetCurrentCamera(_cameras[0]);

    //initialize mesh rendereres
    float* vertices = (float*)malloc(sizeof(float) * amountVertices);
    int* indices = (int*)malloc(sizeof(int) * amountVertices);

    for (int i = 0; i < meshRendereresConfigs.size(); i++)
    {
        YAML::Node node = meshRendereresConfigs[i];

        int countElements = node["vertices"].size();
        for (int j = 0; j < countElements; j++)
        {
            vertices[j + idxVertices] = node["vertices"][j].as<float>();
        }
        idxVertices += countElements;

        countElements = node["indices"].size();
        for (int j = 0; j < countElements; j++)
        {
            indices[j + idxIndices] = node["indices"][j].as<int>();
        }
        std::cout << node << std::endl;
        meshRenderers[i]->baseIndex = idxIndices;
        meshRenderers[i]->amountIndices = countElements;
        meshRenderers[i]->shaderName = node["shader"].as<std::string>();


        idxIndices += countElements;
    }


    //initialize texture names
    std::vector<std::string> _texturesNames;

    for (YAML::Node node : sceneConf["Textures"])
    {
        _texturesNames.push_back(node.as<std::string>());
    }


    SetCurrentCamera(_cameras[0]);

    _sceneRenderer.Setup(vertices, indices, sizeof(float) * amountVertices, sizeof(int) * amountIndices, meshRenderers, _texturesNames, _currentCamera);
}

void Scene::Update()
{
    _sceneRenderer.Render();

}

Scene::~Scene()
{
    _sceneRenderer.cleanUp();
    _gameObjects.clear();
}

void Scene::AddCamera(Camera* camera) 
{
    _cameras.push_back(camera);
}
void Scene::SetCurrentCamera(Camera* camera)
{
    _currentCamera = camera;
}