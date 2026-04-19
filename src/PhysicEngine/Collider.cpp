#include "Collider.h"

#include <Core/Engine.h>

Collider::Collider(GameObject* gameObject, RigidBody* rb) : Component(gameObject), rigidBody(rb)
{
	if (rigidBody == nullptr) 
	{
		rigidBody = gameObject->GetComponent<RigidBody>();
	}

	if (rigidBody == nullptr) 
	{
		std::cout << "No RigidBody found for " << gameObject->name << std::endl;
	}
}

Collider::~Collider()
{
	if (rigidBody && collider) 
	{
		//rigidBody->rigidBody->removeCollider(collider);
	}
}

void Collider::SetBounciness(float bounciness) 
{
	collider->getMaterial().setBounciness(bounciness);
}

void Collider::SetFriction(float friction) 
{
	collider->getMaterial().setFrictionCoefficient(friction);
}

void Collider::setIsTrigger(bool isTrigger)
{
	if (this->isTrigger != isTrigger)
	{
		this->isTrigger = isTrigger;
		collider->setIsTrigger(isTrigger);
	}
}

void Collider::cleanUp()
{
	rigidBody = nullptr;
	collider = nullptr;
}

BoxCollider::BoxCollider(GameObject* gameObject, const glm::vec3& size, const glm::vec3& offset, RigidBody* rb)
	: Collider(gameObject, rb)
{
	rp3d::Vector3 halfSize(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f);
	_shape = Engine::getPhysicsPtr()->getCommon().createBoxShape(halfSize);

	rp3d::Transform colliderTransform(Physics::vecToRP3D(offset), rp3d::Quaternion::identity());
	collider = rigidBody->createCollider(*_shape, colliderTransform);

	collider->getCollideWithMaskBits();
}


void BoxCollider::cleanUp()
{
	Engine::getPhysicsPtr()->getCommon().destroyBoxShape(_shape);
	_shape = nullptr;
	Collider::cleanUp();
}