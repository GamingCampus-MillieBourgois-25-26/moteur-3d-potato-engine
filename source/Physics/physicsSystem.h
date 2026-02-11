#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>

class PhysicsSystem
{
public:
	void Init();
	void Update(float deltaTime);
	
	JPH::PhysicsSystem& GetJoltSystem();

private:
	JPH::PhysicsSystem m_system;

	const JPH::uint cMaxBodies = 65536;
	const JPH::uint cNumBodyMutexes = 0;
	const JPH::uint cMaxBodyPairs = 65536;
	const JPH::uint cMaxContactConstraints = 10240;
};