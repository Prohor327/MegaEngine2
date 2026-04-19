#include "Component.h"

ComponentSystem::Component::Component(GameObject* gameObject)
{
	SetGameObjectPtr(gameObject);
}

GameObject* ComponentSystem::Component::GetGameObjPtr()
{
	return gameObject;
}

void ComponentSystem::Component::SetGameObjectPtr(GameObject* gameObject)
{
	this->gameObject = gameObject;
	transform = &gameObject->transform;
}

void ComponentSystem::Component::SetDeltaTimePtr(float* ptr)
{
	deltaTime = ptr;
}

void ComponentSystem::Component::Start()
{

}

void ComponentSystem::Component::Update()
{

}

void ComponentSystem::Component::OnGameObjectDisable()
{

}

void ComponentSystem::Component::OnGameObjectEnable()
{

}

void ComponentSystem::Component::OnCollisionEnter(GameObject* gameObject)
{

}

void ComponentSystem::Component::OnCollisionStay(GameObject* gameObject)
{

}

void ComponentSystem::Component::OnCollisionExit(GameObject* gameObject)
{

}

void ComponentSystem::Component::OnTriggerEnter(GameObject* gameObject)
{

}

void ComponentSystem::Component::OnTriggerStay(GameObject* gameObject)
{

}

void ComponentSystem::Component::OnTriggerExit(GameObject* gameObject)
{

}