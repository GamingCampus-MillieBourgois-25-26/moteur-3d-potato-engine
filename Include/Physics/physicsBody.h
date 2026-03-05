#pragma once

#include "Maths/Vector3.h"
#include "Maths/Quaternion.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/BodyInterface.h>

#include "Logic/TransformComponent.h"

class PhysicsBody : public Component
{
public:
    PhysicsBody(JPH::BodyID bodyID, JPH::BodyInterface* interfac);

	void SetPosition(Maths::Vec3 position);
	void SetRotation(Maths::Quat rotation);
	
    void SyncFromPhysics(TransformComponent& transform);
    void SyncToPhysics(TransformComponent& transform);

	void AddForce(Maths::Vec3 force);
	void AddImpulse(Maths::Vec3 impulse);

    JPH::BodyID GetID();

private:
    JPH::BodyID m_id;
    JPH::BodyInterface* m_bodyInterface;
};