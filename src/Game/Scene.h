#pragma once

#include <yaml-cpp/yaml.h>

#include <Renderer/SceneRenderer.h>
#include <Game/GameObject.h>
#include <Game/Camera.h>

#include <string>
#include <vector>
#include <memory>
#include <map>

struct Prefab
{
    YAML::Node prefab;
    glm::vec3 offset;
    std::vector<GameObject*> gameObjects;
};

class Scene
{
private:
    SceneRenderer _sceneRenderer;

    std::vector<std::unique_ptr<GameObject>> _gameObjects;
    std::unordered_map<std::string, GameObject*> _namesObjects;
    std::vector<MeshRenderer*> _meshRenderers;
    std::vector<Camera*> _cameras;
    std::vector<GameObject*> _garbage;

    YAML::Node _shaderConf;

    void ClearGarbage();
    void BuildObjectByConfig(const YAML::Node& node, GameObject* gameObject, glm::vec3 offsetPos = vector::zero);
public: 
    Scene(std::string sceneName);
    void Load(std::string sceneName);

    Prefab AddPrefabRuntime(std::string path, glm::vec3 offsetPos = vector::zero);
    void AddObject(const YAML::Node& node, glm::vec3 offsetPos = vector::zero);
    void AddCamera(Camera* camera);
    void destroyGameObject(GameObject* obj);

    Camera* GetCameraPtr();
    GameObject* GetObjectPtrByName(const std::string& name);

    bool ContainsObject(GameObject* gameObject);

    void Update();

    ~Scene();
};