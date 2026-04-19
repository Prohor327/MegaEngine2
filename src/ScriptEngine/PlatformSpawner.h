#pragma once

#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>

namespace Scripts
{
	class PlatformSpawner : public BaseScript
	{
	private:
		glm::vec3 _nextSpawnPoint = vector::zero;
		std::vector<Prefab> _prefabs;

	public:
		ME_PROPERTY(std::string, platform);
		ME_PROPERTY(float, length);
		ME_PROPERTY(Transform*, player);

		void RegisterProperties() override;
		void Start() override;
		void Update() override;
	};

	ME_REGISTER_SCRIPT(PlatformSpawner);
}