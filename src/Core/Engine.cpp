#include "Engine.h"

#include "Core.h"
#include <iostream>

//static DebugRenderer _debugRenderer;
static Physics _physics;
static Scene* _activeScene;

void Engine::setActiveScene(Scene* scene)
{
    _activeScene = scene;
}

void Engine::run()
{
    Core::initalize();

    //_debugRenderer.setup();

    Scene* scene = new Scene("Scene1");
    setActiveScene(scene);

    while (!Core::windowIsOpen())
    {
        _physics.calculate();
        Core::beginFrame();

        _activeScene->Update();

        //_debugRenderer.render();

        Core::endFrame();
    }

    delete scene;
    Core::cleanUp();
}

Scene* Engine::getActiveScenePtr()
{
    return _activeScene;
}

Physics* Engine::getPhysicsPtr()
{
    return &_physics;
}

//DebugRenderer* Engine::getDebugRendererPtr()
//{
//    //return &_debugRenderer;
//}