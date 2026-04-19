#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>

#include <ComponentSystem/Component.h>
#include <PhysicEngine/RigidBody.h>

class RigidBody;

class Collider : public ComponentSystem::Component
{
protected:
	RigidBody* rigidBody;
	rp3d::Collider* collider = nullptr;
	bool isTrigger = false;

	Collider(GameObject* gameObject, RigidBody* rb = nullptr);
	~Collider();

public:
	void SetBounciness(float bounciness);
	void SetFriction(float friction);
	void setIsTrigger(bool isTrigger);
	virtual void cleanUp();
};

class BoxCollider : public Collider
{
private:
	rp3d::BoxShape* _shape;

public:
	BoxCollider(GameObject* gameObject, const glm::vec3& size, const glm::vec3& offset, RigidBody* rb = nullptr);

	void cleanUp() override;
};