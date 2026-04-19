#pragma once

#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>

namespace Scripts
{
	class Cow : public Scripts::BaseScript
	{
	private:
		ME_PROPERTY(float, speed);

		int _coins = 0;

	public:
		//void OnCollisionEnter() override;
		//void OnCollisionStay() override;
		//void OnCollisionExit() override;
		void RegisterProperties() override;
		void Update() override;

		void AddCoin();
	};

	ME_REGISTER_SCRIPT(Cow);
}