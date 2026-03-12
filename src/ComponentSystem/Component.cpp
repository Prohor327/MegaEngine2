#include "Component.h"

ComponentSystem::Component::Component(GameObject* gameObject)
{
	_gameObject = gameObject;
	transform = &gameObject->transform;
}

GameObject* ComponentSystem::Component::GetGameObjPtr()
{
	return _gameObject;
}

void ComponentSystem::Component::Start()
{

}

void ComponentSystem::Component::Update()
{

}

ComponentSystem::Component& ComponentSystem::Component::GetPtr()
{
	return *this;
}
