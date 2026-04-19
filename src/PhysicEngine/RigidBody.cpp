#include "RigidBody.h"

#include <Core/Engine.h>

RigidBody::RigidBody(GameObject* gameObject, BodyType bodyType, float mass, float linearDamping, float angularDamping, bool gravityEnabled)
 : ComponentSystem::Component(gameObject)
{
	this->bodyType = bodyType;
	this->mass = mass;
	this->linearDamping = linearDamping;
	this->angularDamping = angularDamping;
	this->gravityEnabled = gravityEnabled;

	Engine::getPhysicsPtr()->initNewRigidBody(*this);
	this->rigidBody->setUserData(gameObject);

	smoothedTransform = rp3d::Transform();
	rigidBody->setIsDebugEnabled(true);
}

void RigidBody::applyForce(const glm::vec3& force) 
{
	if (rigidBody)
	{
		//_rigidBody->applyExternalForce(rp3d::Vector3(force.x, force.y, force.z));
	}
}

void RigidBody::setVelocity(const glm::vec3& vel)
{
	if (rigidBody)
	{
		rigidBody->setLinearVelocity(rp3d::Vector3(vel.x, vel.y, vel.z));
	}
}

void RigidBody::freezeRotation(const glm::vec3& axis)
{
	isFreezeRotation = true;
	rigidBody->setAngularLockAxisFactor(rp3d::Vector3(0.0f, 0.0f, 0.0f));
}

rp3d::Collider* RigidBody::createCollider(rp3d::CollisionShape& shape, rp3d::Transform offset)
{
	return rigidBody->addCollider(&shape, offset);
}