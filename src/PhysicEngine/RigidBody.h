#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp> 

#include <ComponentSystem/Component.h>
#include <Core/Engine.h>

enum class BodyType 
{
	Static, 
	Kinematic, 
	Dynamic 
};

class RigidBody : public ComponentSystem::Component
{
public:
	float mass = 1.0f;
	float linearDamping = 0.0f;
	float angularDamping = 0.01f;
	bool gravityEnabled = true;
	bool isFreezeRotation = false;
	BodyType bodyType = BodyType::Dynamic;
	rp3d::RigidBody* rigidBody = nullptr;

	rp3d::Transform smoothedTransform;

	RigidBody() = default;
	RigidBody(GameObject* gameObject, BodyType bodyType, float mass, float linearDamping, float angularDamping, bool gravityEnabled);

	void applyForce(const glm::vec3& force);
	void setVelocity(const glm::vec3& vel);

	void freezeRotation(const glm::vec3& axis = vector::zero);

	rp3d::Collider* createCollider(rp3d::CollisionShape& shape, rp3d::Transform offset);
};