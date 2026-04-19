#pragma once

#include"Game/GameObject.h"

class GameObject;

namespace ComponentSystem
{
	class Component
	{

	protected:
		float* deltaTime = nullptr;
		GameObject* gameObject;

	public:
		Transform* transform;

		Component(GameObject* gameObject);
		Component() = default;

		void SetGameObjectPtr(GameObject* gameObject);
		GameObject* GetGameObjPtr();

		void SetDeltaTimePtr(float* ptr);

		virtual void Start();
		virtual void Update();

		virtual void OnGameObjectDisable();
		virtual void OnGameObjectEnable();

		virtual void OnCollisionEnter();
		virtual void OnCollisionStay();
		virtual void OnCollisionExit();

		virtual void OnTriggerEnter();
		virtual void OnTriggerStay();
		virtual void OnTriggerExit();

		virtual ~Component() = default;
	};
}