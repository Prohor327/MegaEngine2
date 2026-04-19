#pragma once

#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>

#include <ScriptEngine/Coin.h>

namespace Scripts
{
	class Road : public BaseScript
	{
	private:
		ME_PROPERTY(std::string, coin);

		std::vector<Scripts::Coin*> _coins;
	public:

		void RegisterProperties() override;
		void Start() override;
		void SpawnCoin(glm::vec3 offset);
		void DestroyCoins();
	};

	ME_REGISTER_SCRIPT(Road);
}