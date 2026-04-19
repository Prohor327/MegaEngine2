#pragma once

#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

#include <Core/Engine.h>
#include <ComponentSystem/Component.h>

namespace Scripts
{
	struct Property
	{
		std::string name;
		Property(std::string name);
		virtual void Serialize(YAML::Node& node) = 0;
		virtual void Deserialize(YAML::Node& node) = 0;

		virtual ~Property() = default;
	};

	template<typename T>
	struct PropertyImpl : Property
	{
		T* valuePtr;

		PropertyImpl(std::string name, T* valuePtr) : Property(name)
		{
			this->valuePtr = valuePtr;
		}

		void Serialize(YAML::Node& node) override
		{
			//node[name] = *valuePtr;
		}

        void Deserialize(YAML::Node& node) override
        {
            if (!node[name])
            {
                return;
            }

            using BaseT = std::remove_pointer_t<T>;

            // ???? ????????
            if constexpr (std::is_pointer_v<T>)
            {
                std::string objName = node[name].template as<std::string>();
                GameObject* targetObj = Engine::getActiveScenePtr()->GetObjectPtrByName(objName);

                if (!targetObj) 
                {
                    *valuePtr = nullptr;
                    return;
                }

                // ???? ?????????
                if constexpr (std::is_base_of_v<ComponentSystem::Component, BaseT>) 
                {
                    *valuePtr = targetObj->GetComponent<BaseT>();
                }
                // ???? ??????? ??????
                else if constexpr (std::is_same_v<GameObject, BaseT>)
                {
                    *valuePtr = targetObj;

                    if (!*valuePtr)
                    {
                        std::cout << "Warning: Object " << objName << " not found!" << std::endl;
                    }
                }
                else if constexpr (std::is_same_v<Transform, BaseT>)
                {
                    *valuePtr =  &targetObj->transform;

                    if (!*valuePtr)
                    {
                        std::cout << "Warning: Object " << objName << " not found!" << std::endl;
                    }
                }
                // ??????
                else 
                {
                    std::cerr << "Error: " << name << " is an unknown pointer type!" << std::endl;
                }
            }
            // ???? ????
            else
            {
                *valuePtr = node[name].template as<T>();
            }
        }

	};
}