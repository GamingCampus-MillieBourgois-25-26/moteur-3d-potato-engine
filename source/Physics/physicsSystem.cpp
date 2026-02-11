#include "physicsSystem.h"

#include "physicsLayerManager.h"

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>


void PhysicsSystem::Init()
{
	JPH::RegisterDefaultAllocator();

	JPH::RegisterTypes();

	PhysicsLayerManager physicsLayerManager;

	m_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, nullptr, &physicsLayerManager, nullptr)
}

void PhysicsSystem::Update(float deltaTime)
{
	
}

JPH::PhysicsSystem& PhysicsSystem::GetJoltSystem()
{
	return m_system;
}