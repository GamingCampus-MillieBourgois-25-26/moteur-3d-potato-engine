#include "physicsBody.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyID.h>

PhysicsBody::PhysicsBody(JPH::BodyID bodyID, JPH::BodyInterface* interface)
	: m_id(bodyID), m_bodyInterface(interface)
{
}

void PhysicsBody::SetPosition(JPH::Vec3 position)
{
	m_bodyInterface->SetPosition(m_id, position, JPH::EActivation::Activate);
}

void PhysicsBody::SetRotation(JPH::Quat rotation)
{
	m_bodyInterface->SetRotation(m_id, rotation, JPH::EActivation::Activate);
}

void PhysicsBody::AddForce(JPH::Vec3 force)
{
	m_bodyInterface->AddForce(m_id, force, JPH::EActivation::Activate);
}

void PhysicsBody::AddImpulse(JPH::Vec3 impulse)
{
	m_bodyInterface->AddImpulse(m_id, impulse);
}

JPH::BodyID PhysicsBody::GetID()
{
	return m_id;
}

void PhysicsBody::SyncFromPhysics(TransformComponent& transform)
{
	transform.localPosition = { m_bodyInterface->GetPosition(m_id).GetX(), m_bodyInterface->GetPosition(m_id).GetY(), m_bodyInterface->GetPosition(m_id).GetZ() };
	
}
void PhysicsBody::SyncToPhysics(TransformComponent& transform)
{
	m_bodyInterface->SetPosition(m_id, JPH::Vec3(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z), JPH::EActivation::Activate);
}


