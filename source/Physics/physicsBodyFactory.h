#pragma once

class PhysicsBodyFactory
{
public:
	PhysicsBody CreateBody(PhysicsSystem system, PhysicsBodyType type, const PhysicsShape& shape, float mass, Vec3 position, Quat rotation);
};