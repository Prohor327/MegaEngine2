#pragma once

#include <vector>

#include <reactphysics3d/reactphysics3d.h>

#include <PhysicEngine/RigidBody.h>
#include <Game/Transform.h>
#include <PhysicEngine/Collider.h>

class RigidBody;
class Collider;

class PhysicsEventListener : public rp3d::EventListener
{
public:

    void onContact(const CallbackData& callbackData) override;

    virtual void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
};

class Physics
{
private:
    reactphysics3d::PhysicsCommon _physicsCommon;
    reactphysics3d::PhysicsWorld* _physicsWorld = nullptr;

    std::vector<RigidBody*> _rigidBodies;
    std::vector<Collider*> _colliders;

    PhysicsEventListener* _listener;

    float _accumulator = 0.0f;

public:
    Physics() = default;
    ~Physics();

    void initNewRigidBody(RigidBody& rb);

    void createNewPhysicsWorld();
    void destroyPhysicsWorld();

    void calculate();

    rp3d::PhysicsWorld* getWorld();
    rp3d::PhysicsCommon& getCommon();

    void removePhysicsComponents(GameObject& gameObject);

    static rp3d::Vector3 vecToRP3D(const glm::vec3& vec);
    static rp3d::Transform transformToRP3D(const Transform& transform);
    static rp3d::Quaternion vecToQuaternion(const glm::vec3& vec);

    static void vecFromRP3D(glm::vec3& out, const rp3d::Vector3 in);
    static void transformFromRP3D(Transform& out, const rp3d::Transform in);
    static void vecFromQuaternion(glm::vec3& out, const rp3d::Quaternion& in);
};