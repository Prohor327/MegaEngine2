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

		virtual void OnCollisionEnter(GameObject* gameObject);
		virtual void OnCollisionStay(GameObject* gameObject);
		virtual void OnCollisionExit(GameObject* gameObject);

		virtual void OnTriggerEnter(GameObject* gameObject);
		virtual void OnTriggerStay(GameObject* gameObject);
		virtual void OnTriggerExit(GameObject* gameObject);

		virtual ~Component() = default;
	};
}