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

void GameObject::OnCollisionEnter()
{
    for (const auto& c : _components)
    {
        c->OnCollisionEnter();
    }
}

void GameObject::OnCollisionStay()
{
    for (const auto& c : _components)
    {
        c->OnCollisionStay();
    }
}


void GameObject::OnCollisionExit()
{
    for (const auto& c : _components)
    {
        c->OnCollisionExit();
    }
}

void GameObject::OnTriggerEnter()
{
    for (const auto& c : _components)
    {
        c->OnTriggerEnter();
    }
}

void GameObject::OnTriggerStay()
{
    for (const auto& c : _components)
    {
        c->OnTriggerStay();
    }
}


void GameObject::OnTriggerExit()
{
    for (const auto& c : _components)
    {
        c->OnTriggerExit();
    }
}