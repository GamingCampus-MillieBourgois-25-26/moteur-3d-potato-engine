#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/RegisterTypes.h>

#include "physicsLayerManager.h"
#include "physicsContactListener.h"
#include "physicsBroadPhaseLayerManager.h"

class PhysicsSystem
{
public:

	PhysicsSystem();

	void Init();
	void Update();
	
	JPH::PhysicsSystem& GetJoltSystem();

private:
	JPH::TempAllocatorImpl temp_allocator;
	JPH::PhysicsSystem m_system;
	JPH::JobSystemThreadPool job_system;
	PhysicsObjectVSBroadPhaseLayerFilter object_vs_broadphase_layer_filter;
	PhysicsContactListener m_contactListener;
	PhysicsBroadPhaseLayerInterface broad_phase_layer_interface;
	PhysicsObjectLayerPairFilter object_vs_object_layer_filter;

	const JPH::uint cMaxBodies = 65536;
	const JPH::uint cNumBodyMutexes = 0;
	const JPH::uint cMaxBodyPairs = 65536;
	const JPH::uint cMaxContactConstraints = 10240;

	const float cDeltaTime = 1.0f / 60.0f;
	const int cCollisionSteps = 1;
};