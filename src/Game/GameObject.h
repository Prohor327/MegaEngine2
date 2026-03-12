#pragma once 

#include "Transform.h"
#include "ComponentSystem/Component.h"

#include <vector>
#include <memory>

namespace ComponentSystem {
    class Component;
}


struct GameObject
{
public:
    Transform transform;

    GameObject(Transform transfrom);
    GameObject() = default;

    template <typename T, typename... Args>
    T& AddComponent(Args&&... args) {
        static_assert(std::is_base_of<ComponentSystem::Component, T>::value, "T must derive from Component");
        std::unique_ptr<T> comp = std::make_unique<T>(std::forward<Args>(args)...); 
        T& reference = *comp;
        _components.push_back(std::move(comp));
        return reference;
    }

    template <typename T>
    T* GetComponent() {
        for (auto& comp : _components) {
            T* casted = dynamic_cast<T*>(comp.get());
            if (casted) return casted;
        }
        return nullptr;
    }

    void Start();
    void Update();
private:
    std::vector<std::unique_ptr<ComponentSystem::Component>> _components;
};