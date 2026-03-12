#pragma once

#include"Game/GameObject.h"

struct GameObject;

namespace ComponentSystem
{
	class Component
	{
	private:
		GameObject* _gameObject = nullptr;

	public:
		[readonly] Transform* transform;
		Component(GameObject* gameObject);
		virtual ~Component() = default;
		GameObject* GetGameObjPtr();
		virtual void Start();
		virtual void Update();
		Component& GetPtr();
	};
}