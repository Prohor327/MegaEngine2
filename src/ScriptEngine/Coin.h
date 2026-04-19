#pragma once

#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>

namespace Scripts
{
	class Coin : public Scripts::BaseScript
	{
	public:
		void OnTriggerEnter() override;
	};

	ME_REGISTER_SCRIPT(Coin);
}