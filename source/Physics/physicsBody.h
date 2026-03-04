#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/BodyInterface.h>

#include "Logic/TransformComponent.h"

class PhysicsBody
{
public:
    PhysicsBody(JPH::BodyID bodyID, JPH::BodyInterface* interface);

    void SetPosition(JPH::Vec3 position);
    void SetRotation(JPH::Quat rotation);
    
    void SyncFromPhysics(TransformComponent& transform);
    void SyncToPhysics(TransformComponent& transform);

    void AddForce(JPH::Vec3 force);
    void AddImpulse(JPH::Vec3 impulse);

    JPH::BodyID GetID();

private:
    JPH::BodyID m_id;
    JPH::BodyInterface* m_bodyInterface;
};