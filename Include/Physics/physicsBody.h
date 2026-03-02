#pragma once

#include "Maths/Vector3.h"
#include "Maths/Quaternion.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Body/BodyInterface.h>

class Transform;

class PhysicsBody
{
public:
	PhysicsBody(JPH::BodyID bodyID, JPH::BodyInterface* interface) : m_id(bodyID), m_bodyInterface(interface) {};

	void SetPosition(Maths::Vec3 position);
	void SetRotation(Maths::Quat rotation);
	
	void SyncFromPhysics(Transform& transform);
	void SyncToPhysics(Transform& transform);

	void AddForce(Maths::Vec3 force);
	void AddImpulse(Maths::Vec3 impulse);

	JPH::BodyID GetID();

private:
	JPH::BodyID m_id;
	JPH::BodyInterface* m_bodyInterface;
};

