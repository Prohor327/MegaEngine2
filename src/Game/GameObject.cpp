#include "GameObject.h"

#include "Renderer/MeshRenderer.h"

GameObject::GameObject(Transform newTransfrom, std::string name, bool active)
    : transform(newTransfrom), name(name)
{
    SetActive(active);
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
    if (!_isActive)
    {
        return;
    }

    for (const auto& c : _components)
    {
        c->Update();
    }
}

void GameObject::SetActive(bool state)
{
    if (state != _isActive)
    {
        _isActive = state;
        
        if (_isActive)
        {
            for (const auto& c : _components)
            {
                c->OnGameObjectEnable();
            }
        }

        if (!_isActive)
        {
            for (const auto& c : _components)
            {
                c->OnGameObjectDisable();
            }
        }
    }
}

bool GameObject::GetActive()
{
    return _isActive;
}

void GameObject::OnCollisionEnter(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnCollisionEnter(gameObject);
    }
}

void GameObject::OnCollisionStay(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnCollisionStay(gameObject);
    }
}


void GameObject::OnCollisionExit(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnCollisionExit(gameObject);
    }
}

void GameObject::OnTriggerEnter(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnTriggerEnter(gameObject);
    }
}

void GameObject::OnTriggerStay(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnTriggerStay(gameObject);
    }
}


void GameObject::OnTriggerExit(GameObject* gameObject)
{
    for (const auto& c : _components)
    {
        c->OnTriggerExit(gameObject);
    }
}