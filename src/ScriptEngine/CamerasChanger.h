#pragma once

#include <ScriptEngine/BaseScript.h>
#include <ScriptEngine/ScriptRegistry.h>
#include <Game/Camera.h>

#include <iostream>
#include <string>


namespace Scripts
{
	class CamerasChanger : public Scripts::BaseScript
	{
	private:
        bool _isKeyPressed = false;
		float _time = 0;

	public:
		ME_PROPERTY(Camera*, Camera1);
		ME_PROPERTY(Camera*, Camera2);
		ME_PROPERTY(GameObject*, Gb1);
		ME_PROPERTY(GameObject*, Gb2);
		ME_PROPERTY(GameObject*, Gb3);
		ME_PROPERTY(std::string, Prefab);

		void RegisterProperties() override;
		void Update() override;
	};

	ME_REGISTER_SCRIPT(CamerasChanger);
}