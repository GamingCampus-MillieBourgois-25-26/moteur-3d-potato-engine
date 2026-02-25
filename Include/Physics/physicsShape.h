#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Core/Reference.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>

enum ShapeType
{
	Box,
	Sphere,
	Capsule
};

class PhysicsShape
{
public:
	ShapeType type;
	virtual ~PhysicsShape() = default;
	virtual JPH::Ref<JPH::Shape> GetJoltShape() const = 0;
};

class BoxShape : public PhysicsShape 
{
public:
	JPH::Vec3 halfExtents;

	BoxShape(JPH::Vec3 halfExtent) : halfExtents(halfExtent){};
};

class SphereShape : public PhysicsShape
{
public:
	float radius;

	SphereShape(float rad) : radius(rad) {};
};

class CapsuleShape : public PhysicsShape 
{
public:
	float radius;
	float height;

	CapsuleShape(float rad, float hgt) : radius(rad), height(hgt) {};
};