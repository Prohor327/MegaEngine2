#pragma once 

#include "Transform.h"
#include "ComponentSystem/Component.h"

#include <vector>
#include <memory>
#include <string>

namespace ComponentSystem 
{
    class Component;
}


class GameObject
{
public:
    Transform transform;
    std::string name;

    GameObject(Transform newTransfrom, std::string name, bool active);
    GameObject() = default;
    virtual ~GameObject() = default;

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) 
    {
        static_assert(std::is_base_of<ComponentSystem::Component, T>::value, "T must derive from Component");
        std::unique_ptr<T> comp = std::make_unique<T>(std::forward<Args>(args)...); 
        T& reference = *comp;
        _components.push_back(std::move(comp));
        return reference;
    }

    void AddComponent(std::unique_ptr<ComponentSystem::Component> component) 
    {
        if (component) 
        {
            _components.push_back(std::move(component));
        }
    }

    template <typename T>
    T* GetComponent() 
    {
        for (auto& comp : _components) 
        {
            T* casted = dynamic_cast<T*>(comp.get());
            if (casted)
            {
                return casted;
            }
        }
        return nullptr;
    }

    void Start();
    void Update();

    void SetActive(bool state);
    bool GetActive();

    void OnCollisionEnter();
    void OnCollisionStay();
    void OnCollisionExit();

    void OnTriggerEnter();
    void OnTriggerStay();
    void OnTriggerExit();

private:
    std::vector<std::unique_ptr<ComponentSystem::Component>> _components;
    bool _isActive;
};