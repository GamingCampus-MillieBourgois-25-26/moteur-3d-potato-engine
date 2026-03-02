#include "Physics/physicsBody.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>

void PhysicsBody::SetPosition(Maths::Vec3 position)
{
	m_bodyInterface->SetPosition(m_id, position, JPH::EActivation::Activate);
}

void PhysicsBody::SetRotation(Maths::Quat rotation)
{
	m_bodyInterface->SetRotation(m_id, rotation, JPH::EActivation::Activate);
}

void PhysicsBody::AddForce(Maths::Vec3 force)
{
	m_bodyInterface->AddForce(m_id, force, JPH::EActivation::Activate);
}

void PhysicsBody::AddImpulse(Maths::Vec3 impulse)
{
	m_bodyInterface->AddImpulse(m_id, impulse);
}

JPH::BodyID PhysicsBody::GetID()
{
	return m_id;
}

void PhysicsBody::SyncFromPhysics(Transform& transform)
{
	return;
}
void PhysicsBody::SyncToPhysics(Transform& transform)
{
	return;
}


