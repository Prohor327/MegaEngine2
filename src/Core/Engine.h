#pragma once

#include <Game/Scene.h>
#include <PhysicEngine/Physics.h>
#include <Renderer/DebugRenderer.h>

class Physics;

namespace Engine 
{
    void run();
    void setActiveScene(Scene* scene);

    Scene* getActiveScenePtr();
    Physics* getPhysicsPtr();
    //DebugRenderer* getDebugRendererPtr();
}