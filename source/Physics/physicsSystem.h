#pragma once
#include "Jolt/Jolt.h"
#include "Jolt/Physics/PhysicsSystem.h"

class PhysicsSystem
{
public:
	void Init();
	void Update(float deltaTime);
	
	JPH::PhysicsSystem GetJoltSystem();

private:
	JPH::PhysicsSystem m_system;
};