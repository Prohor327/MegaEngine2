#pragma once

#include <Renderer/SceneRenderer.h>

#include <string>
#include <vector>
#include <Game/GameObject.h>
#include <Game/Camera.h>
#include <memory>

class Scene
{
private:
    SceneRenderer _sceneRenderer;
    Camera* _currentCamera;
    std::vector<std::unique_ptr<GameObject>> _gameObjects;
    std::vector<Camera*> _cameras;
    
public: 
    Scene(std::string sceneName);
    void Load(std::string sceneName);
    void AddCamera(Camera* camera);
    void SetCurrentCamera(Camera* camera);
    void Update();
    ~Scene();
};