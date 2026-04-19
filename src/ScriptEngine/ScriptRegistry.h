#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

#include <ScriptEngine/BaseScript.h>

#define ME_REGISTER_SCRIPT(ClassName) \
    namespace { \
        struct ClassName##Register { \
            ClassName##Register() { \
                Scripts::ScriptRegistry::Register(#ClassName, []() -> std::unique_ptr<Scripts::BaseScript> { \
                    return std::make_unique<ClassName>(); \
                }); \
            } \
        }; \
        static ClassName##Register global_##ClassName##Register; \
    }

namespace Scripts 
{
	using ScriptCreator = std::function<std::unique_ptr<BaseScript>()>;

	class ScriptRegistry
	{
	private:

		static std::unordered_map<std::string, ScriptCreator>& GetRegistry();

	public:
		static void Register(const std::string& name, ScriptCreator creator);
        static std::unique_ptr<BaseScript> CreateScript(const std::string& name);
	};
}