#include "ScriptRegistry.h"

std::unordered_map<std::string, Scripts::ScriptCreator>& Scripts::ScriptRegistry::GetRegistry()
{
	static std::unordered_map<std::string, ScriptCreator> registry;
	return registry;
}

void Scripts::ScriptRegistry::Register(const std::string& name, ScriptCreator creator)
{
	GetRegistry()[name] = creator;
}

std::unique_ptr<Scripts::BaseScript> Scripts::ScriptRegistry::CreateScript(const std::string& name)
{
	std::unordered_map<std::string, ScriptCreator>& registy = GetRegistry();
	auto it = registy.find(name);

	if (it != registy.end())
	{
		std::unique_ptr<BaseScript> script = it->second();
		script->RegisterProperties();
		return script;
	}

	return nullptr;
}