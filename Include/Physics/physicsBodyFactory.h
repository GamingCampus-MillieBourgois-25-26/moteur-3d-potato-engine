#pragma once
#include "Maths/vector3.cpp"
#include "physicsBody.h"
#include "physicsSystem.h"
#include "physicsTypes.h"
#include "physicsShape.h"

#include <Jolt/Jolt.h>

class PhysicsBodyFactory
{
public:
	PhysicsBody CreateBody(PhysicsSystem system, PhysicsBodyType type, const PhysicsShape& shape, float mass, Maths::Vec3 position, JPH::Quat rotation);
};