#include "physicsSystem.h"

#include <Jolt/Jolt.h>
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/Factory.h>

PhysicsSystem::PhysicsSystem() : temp_allocator(10 * 1024 * 1024)
{
}

void PhysicsSystem::Init()
{	
	JPH::Factory::sInstance = new JPH::Factory();

	JPH::RegisterTypes();

	m_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

	job_system.Init(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);

	m_system.SetGravity(JPH::Vec3(0.0f, -9.81f, 0.0f));

	m_system.SetContactListener(&m_contactListener);
}

void PhysicsSystem::Update(float deltaTime)
{
	m_system.Update(cDeltaTime, cCollisionSteps, &temp_allocator, &job_system);
	printf("hello\n");
}

JPH::PhysicsSystem& PhysicsSystem::GetJoltSystem()
{
	return m_system;
}