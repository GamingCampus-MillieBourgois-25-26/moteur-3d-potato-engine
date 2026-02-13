#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

#include "physicsLayerManager.h"
#include "physicsContactListener.h"

class PhysicsSystem
{
public:
	void Init();
	void Update(float deltaTime);
	
	JPH::PhysicsSystem& GetJoltSystem();

private:
	JPH::PhysicsSystem m_system;

	JPH::TempAllocatorImpl temp_allocator = JPH::TempAllocatorImpl(10 * 1024 * 1024);
	// Managers / listeners stockés ici pour garantir leur durée de vie
	PhysicsLayerManager m_layerManager;
	PhysicsContactListener m_contactListener;

	const JPH::uint cMaxBodies = 65536;
	const JPH::uint cNumBodyMutexes = 0;
	const JPH::uint cMaxBodyPairs = 65536;
	const JPH::uint cMaxContactConstraints = 10240;

	const float cDeltaTime = 1.0f / 60.0f; // 60 ticks par seconde
	const int cCollisionSteps = 1;
};