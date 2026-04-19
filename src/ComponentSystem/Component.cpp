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

void ComponentSystem::Component::OnCollisionEnter()
{

}

void ComponentSystem::Component::OnCollisionStay()
{

}

void ComponentSystem::Component::OnCollisionExit()
{

}

void ComponentSystem::Component::OnTriggerEnter()
{

}

void ComponentSystem::Component::OnTriggerStay()
{

}

void ComponentSystem::Component::OnTriggerExit()
{

}