#include "Scene.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <memory>

#include <ScriptEngine/ScriptRegistry.h>
#include <Renderer/ModelLoader.h>
#include <Game/ResourceManager.h>
#include <Core/Engine.h>

Scene::Scene(std::string sceneName)
{
    Load(sceneName);
}

void Scene::Load(std::string sceneName)
{
    Engine::setActiveScene(this);

    YAML::Node sceneConf = YAML::LoadFile("res/Scenes/" + sceneName + ".yaml");
    _shaderConf = YAML::LoadFile("res/Configs/Shaders.yaml");

    int amountObjects = sceneConf["Objects"].size();

    _gameObjects.clear();

    Engine::getPhysicsPtr()->createNewPhysicsWorld();

    for (int i = 0; i < amountObjects; i++)
    {
        YAML::Node node = sceneConf["Objects"]["obj" + std::to_string(i)];

            AddObject(node);
    }

    //Engine::getDebugRendererPtr()->setPhysicsWorld(Engine::getPhysicsPtr()->getWorld());
    _sceneRenderer.setup(&_meshRenderers);
}

Prefab Scene::AddPrefabRuntime(std::string path, glm::vec3 offsetPos)
{
    Prefab pp;
    pp.prefab = YAML::LoadFile(path);
    pp.offset = offsetPos;

    int amountObjects = pp.prefab["Objects"].size();

    for (int i = 0; i < amountObjects; i++)
    {
        YAML::Node node = pp.prefab["Objects"]["obj" + std::to_string(i)];

        _gameObjects.emplace_back(std::make_unique<GameObject>());
        GameObject* obj = _gameObjects.back().get();

        BuildObjectByConfig(node, obj, offsetPos);
        pp.gameObjects.push_back(obj);
        obj->Start();
    }

    return pp;
}

void Scene::AddObject(const YAML::Node& node, glm::vec3 offsetPos)
{
    _gameObjects.emplace_back(std::make_unique<GameObject>());

    BuildObjectByConfig(node, _gameObjects.back().get(), offsetPos);
    _gameObjects.back()->Start();
}

void Scene::Update()
{
    const size_t count = _gameObjects.size();

    for (size_t i = 0; i < count; ++i)
    {
        if (_gameObjects[i])
        {
            _gameObjects[i]->Update();
        }
    }

    _sceneRenderer.Render();
    ClearGarbage();
}

void Scene::BuildObjectByConfig(const YAML::Node& node, GameObject* gameObject, glm::vec3 offsetPos)
{
    Transform transform;
    for (int j = 0; j < 3; ++j)
    {
        transform.position[j] = node["Transforms"][j].as<float>();
        transform.rotation[j] = node["Transforms"][j + 3].as<float>();
        transform.scale[j] = node["Transforms"][j + 6].as<float>();

        //std::cout << "pos" << node["Transforms"][j].as<float>() << "rot" <<
        //    node["Transforms"][j + 3].as<float>() << "scale" <<
        //    node["Transforms"][j + 6].as<float>() << std::endl;
    }

    transform.position += offsetPos;
    gameObject->transform = transform;

    bool active;

    if (node["Active"])
    {
        active = node["Active"].as<bool>();
    }
    else
    {
        active = true;
    }

    gameObject->SetActive(active);
    gameObject->name = node["Name"].as<std::string>();

    _namesObjects.emplace(gameObject->name, gameObject);


    if (node["Components"]["MeshRenderer"])
    {
        YAML::Node meshRendererConfig = node["Components"]["MeshRenderer"];
        MeshRenderer* meshRenderer = &gameObject->AddComponent<MeshRenderer>();
        meshRenderer->SetGameObjectPtr(gameObject);
        if (meshRendererConfig["Model"])
        {
            meshRenderer->model = ResourceManager::GetInstance().GetModel(meshRendererConfig["Model"].as<std::string>());
        }
        if (meshRendererConfig["Texture"])
        {
            meshRenderer->texture = ResourceManager::GetInstance().GetTexture(meshRendererConfig["Texture"].as<std::string>());
        }
        if (meshRendererConfig["Shader"])
        {
            std::string shaderName = meshRendererConfig["Shader"].as<std::string>();

            if (_shaderConf[shaderName])
            {
                auto sConf = _shaderConf[shaderName];

                meshRenderer->shader = ResourceManager::GetInstance().GetShader(
                    shaderName,
                    sConf["vertex"].as<std::string>(),
                    sConf["fragment"].as<std::string>());
            }
            else
            {
                std::cerr << "Error: Shader '" << shaderName << "' not found in shader config!" << std::endl;
            }
        }
        _meshRenderers.push_back(meshRenderer);
    }

    if (node["Components"]["Camera"])
    {
        YAML::Node cameraNode = node["Components"]["Camera"];
        Camera& camRef = gameObject->AddComponent<Camera>(gameObject,
            cameraNode["Fov"].as<float>(), cameraNode["Far"].as<float>(), cameraNode["Near"].as<float>());
        AddCamera(&camRef);
    }

    if (node["Components"]["RigidBody"])
    {
        YAML::Node rigidBodyNode = node["Components"]["RigidBody"];

        BodyType bodyType;
        std::string bodyTypeStr = rigidBodyNode["BodyType"].as<std::string>();

        if (bodyTypeStr == "Dynamic")
        {
            bodyType = BodyType::Dynamic;
        }
        else if (bodyTypeStr == "Static")
        {
            bodyType = BodyType::Static;
        }
        else if (bodyTypeStr == "Kinematic")
        {
            bodyType = BodyType::Kinematic;
        }
        //std::cout << node["Components"]["RigidBody"] << std::endl;

        RigidBody& rb = gameObject->AddComponent<RigidBody>(gameObject, bodyType, rigidBodyNode["Mass"].as<float>(),
            rigidBodyNode["LinearDamping"].as<float>(), rigidBodyNode["AngularDamping"].as<float>(),
            rigidBodyNode["GravityEnabled"].as<bool>());

        if (rigidBodyNode["FreezeRotation"] && rigidBodyNode["FreezeRotation"].as<bool>() == true)
        {
            rb.freezeRotation();
        }
    }

    if (node["Components"]["BoxCollider"])
    {
        YAML::Node colliderNode = node["Components"]["BoxCollider"];

        glm::vec3 size(colliderNode["Size"][0].as<float>(), colliderNode["Size"][1].as<float>(), colliderNode["Size"][2].as<float>());
        glm::vec3 offset(colliderNode["Offset"][0].as<float>(), colliderNode["Offset"][1].as<float>(), colliderNode["Offset"][2].as<float>());

        Collider& collider = gameObject->AddComponent<BoxCollider>(gameObject, size, offset, gameObject->GetComponent<RigidBody>());

        if (colliderNode["IsTrigger"] && colliderNode["IsTrigger"].as<bool>() == true)
        {
            collider.setIsTrigger(true);
        }
    }

    if (node["Components"]["Scripts"])
    {
        //std::cout << node["Components"]["Scripts"] << std::endl;
        auto scriptsNode = node["Components"]["Scripts"];

        for (auto it : scriptsNode)
        {
            std::string scriptName = it.first.as<std::string>();
            YAML::Node scriptData = it.second;
            auto script = Scripts::ScriptRegistry::CreateScript(scriptName);

            if (script)
            {
                script->SetGameObjectPtr(gameObject);
                script->Deserialize(scriptData);
                script->SetDeltaTimePtr(Core::getDeltaTimePtr());
                gameObject->AddComponent(std::move(script));
                //std::cout << "Successfully added: " << scriptName << std::endl;
            }
            else
            {
                std::cerr << "Error: Script " << scriptName << " not found in Registry!" << std::endl;
            }
        }
    }
}

void Scene::AddCamera(Camera* camera) 
{
    _cameras.push_back(camera);
}

Camera* Scene::GetCameraPtr()
{
    for (Camera* cam : _cameras)
    {
        if (cam->GetGameObjPtr()->GetActive())
        {
            return cam;
        }
    }

    //std::cout << "No Active Camera On Scene" << std::endl;
    return nullptr;
}

GameObject* Scene::GetObjectPtrByName(const std::string& name)
{
    auto it = _namesObjects.find(name);

    if (it != _namesObjects.end()) {
        return it->second;
    }

    return nullptr;
}

void Scene::ClearGarbage()
{
    for (GameObject* obj : _garbage)
    {
        //std::cout << obj->name << std::endl;
        _namesObjects.erase(obj->name);
        _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), obj->GetComponent<Camera>()), _cameras.end());
        _meshRenderers.erase(
            std::remove(_meshRenderers.begin(), _meshRenderers.end(), obj->GetComponent<MeshRenderer>()),
            _meshRenderers.end()
        );

        Engine::getPhysicsPtr()->removePhysicsComponents(*obj);

        _gameObjects.erase(
            std::remove_if(_gameObjects.begin(), _gameObjects.end(),
                [obj](const std::unique_ptr<GameObject>& ptr) {
                    return ptr.get() == obj;
                }),
            _gameObjects.end());
    }

    _garbage.clear();
}

bool Scene::ContainsObject(GameObject* gameObject)
{
    if (!gameObject) return false;

    return std::any_of(_gameObjects.begin(), _gameObjects.end(),
        [gameObject](const std::unique_ptr<GameObject>& ptr) {
            return ptr.get() == gameObject;
        });
}

void Scene::destroyGameObject(GameObject* obj)
{
    if (obj == nullptr)
    {
        std::cout << "Deleting GB is null" << std::endl;
    }
    _garbage.push_back(obj);
}

Scene::~Scene()
{
    _sceneRenderer.cleanUp();
    _gameObjects.clear();
    Engine::getPhysicsPtr()->destroyPhysicsWorld();
}