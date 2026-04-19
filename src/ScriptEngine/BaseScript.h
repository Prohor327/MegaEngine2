#pragma once

#include <Game/GameObject.h>
#include <ScriptEngine/Properties.h>
#include <ComponentSystem/Component.h>

#include <vector>
#include <memory>

#define ME_PROPERTY(type, name) \
    type name; \
    void Register_##name() { RegisterProperty(#name, &name); }


namespace Scripts
{
    class BaseScript : public ComponentSystem::Component
    {
    private:
        std::vector<std::shared_ptr<Property>> _properties;

    public:
        template<typename T>
        void RegisterProperty(std::string name, T* value)
        {
            _properties.push_back(std::make_shared<PropertyImpl<T>>(name, value));
        }

        void Serialize(YAML::Node& node);
        void Deserialize(YAML::Node& node);

        virtual void RegisterProperties();

        virtual ~BaseScript() = default;
    };
}