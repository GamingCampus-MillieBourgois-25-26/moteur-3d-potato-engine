#include "physicsSystem.h"

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/TempAllocator.h>


void PhysicsSystem::Init()
{
	JPH::RegisterDefaultAllocator();

	JPH::RegisterTypes();

	m_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, nullptr, &m_layerManager, nullptr);

	m_system.SetGravity(JPH::Vec3(0.0f, -9.81f, 0.0f));

	m_system.SetContactListener(&m_contactListener);

	
}

void PhysicsSystem::Update(float deltaTime)
{
	// TODO
	//m_system.Update(cDeltaTime, cCollisionSteps, &temp_allocator, ???);
}

JPH::PhysicsSystem& PhysicsSystem::GetJoltSystem()
{
	return m_system;
}