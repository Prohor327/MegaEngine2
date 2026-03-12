#include "Engine.h"

#include "Core.h"
#include "Game/Scene.h"
#include "Renderer/Shader.h"
#include <iostream>

void Engine::run()
{
    Core::initalize();
    Scene *scene = new Scene("Scene1");

    while(!Core::windowIsOpen())
    {
        Core::beginFrame();
        scene->Update();
        Core::endFrame();
    }

    delete scene;
    Core::cleanUp();
}