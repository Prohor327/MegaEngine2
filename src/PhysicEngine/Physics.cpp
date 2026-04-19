#include "Physics.h"

#include <algorithm>

#include <Core/Core.h>

constexpr static float _timeStep = 1.0f / 165.0f;
constexpr static float maxAccumulator = 0.25f;

void PhysicsEventListener::onContact(const CallbackData& callbackData)
{
    for(int i = 0; i < callbackData.getNbContactPairs(); i++)
    {
        ContactPair contactPair = callbackData.getContactPair(i);

        GameObject* obj1 = static_cast<GameObject*>(contactPair.getBody1()->getUserData());
        GameObject* obj2 = static_cast<GameObject*>(contactPair.getBody2()->getUserData());

        switch (contactPair.getEventType())
        {
        case ContactPair::EventType::ContactStart:
            obj1->OnCollisionEnter(obj2);
            obj2->OnCollisionEnter(obj1);
            break;
        case ContactPair::EventType::ContactStay:
            obj1->OnCollisionStay(obj2);
            obj2->OnCollisionStay(obj1);
            break;
        case ContactPair::EventType::ContactExit:
            obj1->OnCollisionExit(obj2);
            obj2->OnCollisionExit(obj1);
            break;
        }
    }
}

void PhysicsEventListener::onTrigger(const rp3d::OverlapCallback::CallbackData & callbackData)
{
    for (int i = 0; i < callbackData.getNbOverlappingPairs(); i++)
    {
        rp3d::OverlapCallback::OverlapPair overlapPair = callbackData.getOverlappingPair(i);

        GameObject* obj1 = static_cast<GameObject*>(overlapPair.getBody1()->getUserData());
        GameObject* obj2 = static_cast<GameObject*>(overlapPair.getBody2()->getUserData());

        switch (overlapPair.getEventType())
        {
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart:
            obj1->OnTriggerEnter(obj2);
            obj2->OnTriggerEnter(obj1);
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStay:
            obj1->OnTriggerStay(obj2);
            obj2->OnTriggerStay(obj1);
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit:
            obj1->OnTriggerExit(obj2);
            obj2->OnTriggerExit(obj1);
            break;
        }
    }
}

Physics::~Physics()
{
    destroyPhysicsWorld();
}


void Physics::initNewRigidBody(RigidBody& rb)
{
    rb.rigidBody = _physicsWorld->createRigidBody(transformToRP3D(*rb.transform));

    switch (rb.bodyType)
    {
    case BodyType::Dynamic:
        rb.rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
        break;
    case BodyType::Static:
        rb.rigidBody->setType(reactphysics3d::BodyType::STATIC);
        break;
    case BodyType::Kinematic:
        rb.rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
        break;
    }

    _rigidBodies.push_back(&rb);
}

void Physics::createNewPhysicsWorld()
{
    _physicsWorld = _physicsCommon.createPhysicsWorld();
    _listener = new PhysicsEventListener();
    _physicsWorld->setEventListener(_listener);
}

void Physics::destroyPhysicsWorld()
{
    _physicsCommon.destroyPhysicsWorld(_physicsWorld);
    _physicsWorld = nullptr;
}

void Physics::calculate()
{
    _accumulator += Core::getDeltaTime();

    if (_accumulator > maxAccumulator)
    {
        _accumulator = maxAccumulator;
    }

    for (RigidBody* rb : _rigidBodies)
    {
        rb->rigidBody->setTransform(transformToRP3D(*rb->transform));
    }

    while (_accumulator >= _timeStep)
    {
        _physicsWorld->update(_timeStep);
        _accumulator -= _timeStep;
    }

    for (RigidBody* rb : _rigidBodies)
    {
        if (rb->rigidBody->getType() == rp3d::BodyType::STATIC || rb->rigidBody->isSleeping())
            continue;

        transformFromRP3D(*rb->transform, rb->rigidBody->getTransform());
    }
}

rp3d::PhysicsWorld* Physics::getWorld()
{
    return _physicsWorld;
}

rp3d::PhysicsCommon& Physics::getCommon()
{
    return _physicsCommon;
}

void Physics::removePhysicsComponents(GameObject& gameObject)
{
    Collider* collider = gameObject.GetComponent<Collider>();
    RigidBody* rb = gameObject.GetComponent<RigidBody>();

    if (rb != nullptr && rb->rigidBody != nullptr)
    {
        _physicsWorld->destroyRigidBody(rb->rigidBody);
        rb->rigidBody = nullptr;

        _rigidBodies.erase(
            std::remove(_rigidBodies.begin(), _rigidBodies.end(), rb),
            _rigidBodies.end()
        );
    }

    if (collider != nullptr)
    {
        collider->cleanUp();
    }
}

inline rp3d::Vector3 Physics::vecToRP3D(const glm::vec3& vec)
{
    return rp3d::Vector3(vec.x, vec.y, vec.z);
}

inline rp3d::Transform Physics::transformToRP3D(const Transform& transform)
{
    glm::vec3 rotRad = glm::radians(transform.rotation);
    return rp3d::Transform(vecToRP3D(transform.position), vecToQuaternion(rotRad));
}

inline rp3d::Quaternion Physics::vecToQuaternion(const glm::vec3& rotRad)
{
    glm::quat quat = glm::angleAxis(rotRad.z, glm::vec3(0, 0, 1)) * glm::angleAxis(rotRad.y, glm::vec3(0, 1, 0)) * glm::angleAxis(rotRad.x, glm::vec3(1, 0, 0));
    return rp3d::Quaternion(quat.x, quat.y, quat.z, quat.w);
}

inline void Physics::vecFromRP3D(glm::vec3& out, const rp3d::Vector3 in)
{
    out = glm::vec3(in.x, in.y, in.z);
}

inline void Physics::transformFromRP3D(Transform& out, const rp3d::Transform in)
{
    vecFromRP3D(out.position, in.getPosition());
    vecFromQuaternion(out.rotation, in.getOrientation());
    out.rotation = glm::degrees(out.rotation);
}

inline void Physics::vecFromQuaternion(glm::vec3& out, const rp3d::Quaternion& in)
{
    out = glm::eulerAngles(glm::quat(in.w, in.x, in.y, in.z));
}