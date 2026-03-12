#include "GameObject.h"

#include "Renderer/MeshRenderer.h"

GameObject::GameObject(Transform transform)
{
    this->transform = transform;
    _components.clear();
}

void GameObject::Start()
{
    for (const auto& c : _components)
    {
        c->Start();
    }
}

void GameObject::Update()
{
    for (const auto& c : _components)
    {
        c->Update();
    }
}